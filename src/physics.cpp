#include "physics.h"

Physics::Physics(){
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    init();
}

Physics::~Physics(){
    deleteAllObjects();
    delete collisionConfiguration;
    delete dispatcher;
    delete overlappingPairCache;
    delete solver;
    delete dynamicsWorld;
}

void Physics::init(){
    dynamicsWorld->setGravity(btVector3(0, -20, 0));
    
}

btRigidBody* Physics::makeStaticBox(btVector3 size, btVector3 origin, int id){
    btCollisionShape* boxShape = new btBoxShape(size);
    collisionShapes.push_back(boxShape);

    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(origin);

    btScalar mass(0.);//箱は静的剛体とする
    btVector3 localInertia(0, 0, 0);

    btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, boxShape, localInertia);
    //rbInfo.m_restitution = 0.5; //定数の設定法

    btRigidBody* body = new btRigidBody(rbInfo);

    body->setUserIndex(id);
    body->setUserIndex2(0);

    dynamicsWorld->addRigidBody(body);    

    return body;
}

btRigidBody* Physics::makeSphere(btScalar radius, btVector3 origin, int id){
    btCollisionShape* colShape = new btSphereShape(radius);
    collisionShapes.push_back(colShape);

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(origin);

    btScalar mass(1.f);

    btVector3 localInertia(0, 0, 0);
    colShape->calculateLocalInertia(mass, localInertia);

    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
    rbInfo.m_restitution = 0.;

    btRigidBody* body = new btRigidBody(rbInfo);

    dynamicsWorld->addRigidBody(body);
    body->setUserIndex(id);
    body->setUserIndex2(1);

    return body;
}

void Physics::deleteObjects(btRigidBody* body){
    if(body && body->getMotionState()) delete body->getMotionState();
    dynamicsWorld->removeRigidBody(body);
    delete body;
    body = nullptr;
    return ;
}

//放置　仕様側で書くべきと判断
void Physics::doSimulation(){
    dynamicsWorld->stepSimulation(1.f / 60.f, 10);

    for(int j = 0 ;j < dynamicsWorld->getNumCollisionObjects(); j++)
    {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
        btRigidBody* body = btRigidBody::upcast(obj);
        btTransform trans;
        if(body && body->getMotionState())
        {
            body->getMotionState()->getWorldTransform(trans);
        }else{
            trans = obj->getWorldTransform();
        }
    }

}

void Physics::checkCollision(){
    btDispatcher* dispatcher =  dynamicsWorld->getDispatcher();
    int num_manifolds = dispatcher->getNumManifolds();
    collisionData.clear();//初期化する

    for(int i = 0; i < num_manifolds; i++){
        btPersistentManifold *manifold = dispatcher->getManifoldByIndexInternal(i);

        //btCollisionObject* obA = const_cast<btCollisionObject*> (manifold->getBody0());
        //btCollisionObject* obB = const_cast<btCollisionObject*> (manifold->getBody1());
        btCollisionObject* obA = dynamicsWorld->getCollisionObjectArray()[manifold->getBody0()->getWorldArrayIndex()];
        btCollisionObject* obB = dynamicsWorld->getCollisionObjectArray()[manifold->getBody1()->getWorldArrayIndex()];


        int num_contacts = manifold->getNumContacts();
        for(int j = 0; j < num_contacts; j++){
            btManifoldPoint& pt = manifold->getContactPoint(j);
            if(pt.getDistance() <= 0.f){
                CollisionData data = {
                    .bodyA = btRigidBody::upcast(obA),
                    .bodyB = btRigidBody::upcast(obB),
                    .ptA = pt.getPositionWorldOnA(),
                    .ptB = pt.getPositionWorldOnB()
                    };
                collisionData.push_back(data);
                //btVector3& normalOnB = pt.m_normalWorldOnB;
            }
        }
    }
}

void Physics::deleteAllObjects(){
    for(int i = dynamicsWorld->getNumCollisionObjects()-1; i >= 0; i--)
    {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if(body && body->getMotionState()){
            delete body->getMotionState();
        }
        dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    for(int j = 0; j < collisionShapes.size(); j++)
    {
        btCollisionShape* shape = collisionShapes[j];
        collisionShapes[j] = 0;
        delete shape;
    }
}