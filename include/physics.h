#include "btBulletDynamicsCommon.h"

//userindex 全体的なid 

class Physics
{
public:
    Physics();
    ~Physics();
    void doSimulation();
    
    btRigidBody* makeStaticBox(btVector3 size, btVector3 origin, int id);
    btRigidBody* makeSphere(btScalar radius, btVector3 origin, int id);

    btDiscreteDynamicsWorld* getDynamicWorld(){
        return dynamicsWorld;
    }

private:
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    
    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    void init();
    void deleteAllObjects();
};
