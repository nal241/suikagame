#pragma once
#include "btBulletDynamicsCommon.h"

#include <vector>


struct CollisionData{
    btRigidBody* bodyA;
    btRigidBody* bodyB;
    const btVector3& ptA;
    const btVector3& ptB;
};

//userindex 全体的なid 

class Physics
{
public:
    Physics();
    ~Physics();
    void doSimulation();
    
    btRigidBody* makeStaticBox(btVector3 size, btVector3 origin, int id);
    btRigidBody* makeSphere(btScalar radius, btVector3 origin, int id);

    void deleteObjects(btRigidBody* body);

    btDiscreteDynamicsWorld* getDynamicWorld(){
        return dynamicsWorld;
    }
    
    const std::vector<CollisionData>& getCollisionData(){
        return collisionData;
    }
    
    btDiscreteDynamicsWorld* dynamicsWorld;
    std::vector<CollisionData> collisionData;
    void checkCollision();
private:
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    
    btAlignedObjectArray<btCollisionShape*> collisionShapes;
    
    

    void init();
    void deleteAllObjects();
};
