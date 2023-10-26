#include "sceneGame.h"

#include <GL/glut.h>
#include <string>

#include "eScene.h"
#include "define.h"
#include "GLdraw.h"
#include "key.h"
#include "define.h"

const char* SceneGame::ParameterTestTag = "test";
int SceneGameId = 1;
int SpaceDown = 0;

SceneGame::SceneGame(Parameter& param, void (* changeScenePtr)(const eScene, Parameter&, const bool)):AbstractScene(param, changeScenePtr)
{
	testParameter = param.get(ParameterTestTag);
    keyboard::clearKeyState();
}

void SceneGame::display(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, WINDOW_X / (double)WINDOW_Y, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(20., 20., 10., 0, 5., 0, 0, 1.0, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();

    for(const auto& item: objects){
        item.second->draw();
    }


    glPopMatrix();

	glutSwapBuffers();
}

void SceneGame::update(){
    //シミュレーション更新
    physics.dynamicsWorld->stepSimulation(1.f/ 60.f);
    physics.checkCollision();

    //オブジェクトの位置情報を更新
    for(const auto& item: objects){
        auto object = item.second;
        btTransform trans;
        btRigidBody* body = object->body;
        body->getMotionState()->getWorldTransform(trans);
        trans.getOpenGLMatrix(object->m);
        object->setPosition(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
    }

    for(const auto& item: objects){
        auto object = item.second;
        btTransform trans;
        btRigidBody* body = object->body;
        body->getMotionState()->getWorldTransform(trans);
        trans.getOpenGLMatrix(object->m);
        object->setPosition(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
    }



    //衝突時の処理（フルーツマージ）
    auto collisionData = physics.getCollisionData();
    for(size_t i = 0; i < collisionData.size(); i++){
        //printf("id: %d %d\n",  collisionData[i].bodyA->getUserIndex2(), collisionData[i].bodyB->getUserIndex2());
        if(collisionData[i].bodyA->getUserIndex2() == 1 && collisionData[i].bodyB->getUserIndex2() == 1){
            //フルーツを消して、新たに追加
            btRigidBody* bodyA = collisionData[i].bodyA;
            btRigidBody* bodyB = collisionData[i].bodyB;

            physics.deleteObjects(bodyA);
            physics.deleteObjects(bodyB);
            objects.erase(bodyA->getUserIndex());
            objects.erase(bodyB->getUserIndex());
            fruits.erase(bodyA->getUserIndex());
            fruits.erase(bodyB->getUserIndex());

            double x,y,z;
            x = collisionData[i].ptA.getX();
            y = collisionData[i].ptA.getY();
            z = collisionData[i].ptA.getZ();
            auto fruit = std::make_shared<Fruit>(x, y, z, SceneGameId);
            fruits[SceneGameId] = fruit;
            objects[SceneGameId] = fruit;
            fruit->body = physics.makeSphere(fruit->getRadius(), btVector3(x, y, z), SceneGameId);
            SceneGameId++;
        }
    }



    //キーボード操作
    if(keyboard::getKeyState(' ') && SpaceDown == 0){
        SpaceDown = 1;
        //フルーツ作る
        auto fruit = std::make_shared<Fruit>(0, 10, 0, SceneGameId);
        fruits[SceneGameId] = fruit;
        objects[SceneGameId] = fruit;
        fruit->body = physics.makeSphere(fruit->getRadius(), btVector3(0, 10, 0), SceneGameId);

        SceneGameId++;

    }else if(!keyboard::getKeyState(' ') && SpaceDown == 1){
        SpaceDown = 0;
    }

    glutPostRedisplay();
}