#include "sceneGame.h"

#include <GL/glut.h>
#include <string>

#include "eScene.h"
#include "define.h"
#include "GLdraw.h"
#include "key.h"
#include "define.h"
#include "sceneGameOver.h"

const char* SceneGame::ParameterTestTag = "test"; 

SceneGame::SceneGame(Parameter& param, void (* changeScenePtr)(const eScene, Parameter&, const bool)):AbstractScene(param, changeScenePtr), player(0.0, BOX_HEIGHT + PLAYER_FROM_BOX_HEIGHT, 0.0)
{
	testParameter = param.get(ParameterTestTag);

    std::uniform_int_distribution<int> dist(MIN_FRUIT_NAME, MAX_FRUIT_NAME);
    current_fruit_name = dist(random);
    next_fruit_name = dist(random);

    //プレイヤーの初期化
    player.fruit = std::make_shared<Fruit>(player.x, player.y, player.z, object_id++, current_fruit_name);
    player.fruitValid = 1;//フルーツを設定したら有効化

    player.falling = 0;//しなくても初期化済み
    player.visible = 1;//しなくても初期化済み

    next_fruit = std::make_shared<Fruit>(player.x, player.y, player.z, object_id++, next_fruit_name);

    keyboard::clearKeyState();
    initStage();
    glClearColor(0.7765, 0.5568, 0.3176, 0.0);

}

void SceneGame::display(){
    //3D初期化
    glViewport(0.0, 0.0, WINDOW_X, WINDOW_Y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, WINDOW_X / (double)WINDOW_Y, 0.1, 100);


    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(0., BOX_HEIGHT * 2.0, BOX_WIDTH * 2.0, 0, BOX_HEIGHT / 2.0, 0, 0, 1.0, 0);
    //gluLookAt(0.1, 50., 0., 0, 10., 0, 0, 0, -1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    drawStage();

    //ライトの設定
    GLfloat lightpos[] = {0, 30., 0., 1.0f};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat diffuse[] = {0.6, 0.6, 0.6, 1.0};
    GLfloat ambient[] = {0.5, 0.5, 0.5, 1.0};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    for(const auto& item: objects){
        item.second->draw();
    }
    //プレイヤーを描画
    if(player.visible){
        player.fruit->draw();
        glDisable(GL_LIGHTING);
        glColor3f(1.0,1.0,1.0);
        glLineWidth(1.0);
        glBegin( GL_LINES );
        glVertex3f(player.x, 0, player.z);
        glVertex3f(player.x, player.y, player.z);
        glEnd();
        glEnable(GL_LIGHTING);
    }

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    //上からの視点
    glViewport(900, 100, 300, 300);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, -BOX_WIDTH, BOX_HEIGHT*1.5, -0.1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
	glLoadIdentity();

    glRotatef(-90, 1.0, 0, 0);

    drawStage();
    for(const auto& item: objects){
        item.second->draw();
    }
    glDisable(GL_DEPTH_TEST);

    glTranslatef(player.x, player.y, player.z);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(0.3, 20, 20);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();


    displayUI();

    glFlush();
	glutSwapBuffers();
}

void SceneGame::displayUI(){
    //2D初期化
    glViewport(0.0, 0.0, WINDOW_X, WINDOW_Y);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    //gluOrtho2D(0, WINDOW_X, WINDOW_Y, 0);
    glOrtho(0, WINDOW_X, WINDOW_Y, 0, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1,1,1);


    std::string str = "Score";
    drawString(str, 100, 60);

    str = std::to_string(score);
    drawString(str, 100, 100);
    
    str = "Next";
    drawString(str, 950, 60);
    glPushMatrix();
    glTranslatef(975, 150, 0);
    glColor3fv(next_fruit->getColor());

    glutSolidSphere(next_fruit->getRadius() * 30.0, 50, 50);
    glPopMatrix();

    //2D後始末
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void SceneGame::update(){
    //シミュレーション更新
    physics.dynamicsWorld->stepSimulation(1.f/ 60.f);
    physics.checkCollision();

    //オブジェクトの位置情報を更新、描画
    for(const auto& item: objects){
        auto object = item.second;
        btTransform trans;
        btRigidBody* body = object->body;
        body->getMotionState()->getWorldTransform(trans);
        trans.getOpenGLMatrix(object->m);
        object->setPosition(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
    }
    //プレイヤーの位置を更新
    if(player.visible)player.updatePosition();

    glutPostRedisplay();


    {//衝突時の処理（フルーツマージ）
    auto collisionData = physics.getCollisionData();
    int merge = 0;
    size_t merge_arg;
    for(size_t i = 0; i < collisionData.size(); i++){//このループ内ではcollisionDataの中身を変更しないように、フラグの処理のみする
        //フルーツの合体チェック
        if(collisionData[i].bodyA->getUserIndex2() == 1 && collisionData[i].bodyB->getUserIndex2() == 1){
            auto fruitA = fruits[collisionData[i].bodyA->getUserIndex()];
            auto fruitB = fruits[collisionData[i].bodyB->getUserIndex()];
            if(fruitA == nullptr || fruitB == nullptr) {fprintf(stderr, "fruit Pointer error"); exit(1);}
            if(fruitA->getFruitName() == fruitB->getFruitName()) {merge = 1; merge_arg = i;}           
        }
        //プレイヤーが落下済みかチェック
        if(player.falling && (collisionData[i].bodyA->getUserIndex() == player.fruit->getId() || collisionData[i].bodyB->getUserIndex() == player.fruit->getId())){
            player.falling = 0;//playerが落下
        }
        //すべて済みならbreak
        if(merge && !player.falling) break;
    }

    //collisionの結果を受けて

    //フルーツを合体
    if(merge)mergeFruit(collisionData[merge_arg].bodyA->getUserIndex(), collisionData[merge_arg].bodyB->getUserIndex(), collisionData[merge_arg].ptA);
    //playerをnextに
    if(!player.fruitValid && !player.falling){
        //nextを更新
        std::uniform_int_distribution<int> dist(MIN_FRUIT_NAME, MAX_FRUIT_NAME);
        current_fruit_name = next_fruit_name;
        next_fruit_name = dist(random);
        player.fruit = next_fruit;
        next_fruit = std::make_shared<Fruit>(player.x, player.y, player.z, object_id++, next_fruit_name);
        player.fruitValid = 1;
        player.visible = 1;
        player.updatePosition();

    }
    }


    //キーボード操作
    if(keyboard::getKeyState(' ') && key_available[' '] == 0){
        key_available[' '] = 1;

        //playerを登録
        if(!player.falling){
            fruits[player.fruit->getId()] = player.fruit;
            objects[player.fruit->getId()] = player.fruit;
            player.fruit->body = physics.makeSphere(player.fruit->getRadius(), btVector3(player.x, player.y, player.z), player.fruit->getId());
            player.falling = 1;
            player.visible = 0;
            player.fruitValid = 0;
        }


    }else if(!keyboard::getKeyState(' ') && key_available[' '] == 1){
        key_available[' '] = 0;
    }else if(keyboard::getKeyState('0')) exit(0);

    if(!player.falling){
        double x_limit,z_limit;
        x_limit = BOX_WIDTH/2.0 - PLAYER_MOVABLE_WIDTH;
        z_limit = x_limit;

        if(keyboard::getKeyState('w') && -z_limit < player.z)player.z -= 0.1;
        if(keyboard::getKeyState('s') && player.z < z_limit)player.z += 0.1;
        if(keyboard::getKeyState('a') && -x_limit < player.x)player.x -= 0.1;
        if(keyboard::getKeyState('d') && player.x < x_limit)player.x += 0.1;
    }
    
    if(!player.falling)checkGameOver();
    if(isGameOver()){
        Parameter parameter;
        parameter.set(SceneGameOver::ResultTag, score);
        changeScene(SCENE_GAME_OVER, parameter, 0);
    }

    if(keyboard::getKeyState('o')) gameOver =1;

    if(keyboard::getKeyState('p')){
        Parameter parameter;
        parameter.set(SceneGameOver::ResultTag, score);
        changeScene(SCENE_GAME_PAUSE, parameter, 0);
    }

}

int SceneGame::mergeFruit(int idA, int idB, btVector3 Point){
    auto fruitA = fruits[idA];
    auto fruitB = fruits[idB];
    if(fruitA == nullptr || fruitB == nullptr) {fprintf(stderr, "eixted mergeFruit:id %d %d/n", idA, idB); exit(1);}
    if(fruitA->getFruitName() != fruitB->getFruitName()) return 0;

    //スコアをアップ
    const int fruit_score[] = {1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66};
    score += fruit_score[fruitA->getFruitName()];

    //Aは消す
    physics.deleteObjects(fruitA->body);
    objects.erase(fruitA->body->getUserIndex());
    fruits.erase(fruitA->body->getUserIndex());
    //Bは次にする
    
    physics.deleteObjects(fruitB->body);
    if(fruitB->getFruitName() < fruitB->MAX_FRUIT_NAME_TYPE){
        fruitB->stepUp();
        fruitB->body = physics.makeSphere(fruitB->getRadius(), Point, fruitB->getId());
        fruitB->body->getWorldTransform().setOrigin(Point);
    }else{
    objects.erase(fruitB->body->getUserIndex());
    fruits.erase(fruitB->body->getUserIndex());        
    }
    return 1;
}

void SceneGame::initStage(){
    double h = BOX_HEIGHT / 2.0;
    double w = BOX_WIDTH / 2.0;
    //1の厚さの壁
    physics.makeStaticBox(btVector3(w+1, h, w+1), btVector3(0, -h, 0), 0);
    physics.makeStaticBox(btVector3(w+1, h, w+1), btVector3(BOX_WIDTH+1, h, 0), 0);
    physics.makeStaticBox(btVector3(w+1, h, w+1), btVector3(-(BOX_WIDTH+1), h, 0), 0);
    physics.makeStaticBox(btVector3(w+1, h, w+1), btVector3(0, h, BOX_WIDTH+1), 0);
    physics.makeStaticBox(btVector3(w+1, h, w+1), btVector3(0, h, -(BOX_WIDTH+1)), 0);
}

void SceneGame::drawStage(){
    GLdouble Point0[] = {BOX_WIDTH/2.0 ,0 ,BOX_WIDTH/2.0};
	GLdouble Point1[] = {-BOX_WIDTH/2.0 ,0 ,BOX_WIDTH/2.0};
	GLdouble Point2[] = {-BOX_WIDTH/2.0 ,0 ,-BOX_WIDTH/2.0};
	GLdouble Point3[] = {BOX_WIDTH/2.0 ,0 ,-BOX_WIDTH/2.0};
    GLdouble Point4[] = {BOX_WIDTH/2.0 ,BOX_HEIGHT ,BOX_WIDTH/2.0};
	GLdouble Point5[] = {-BOX_WIDTH/2.0 ,BOX_HEIGHT ,BOX_WIDTH/2.0};
	GLdouble Point6[] = {-BOX_WIDTH/2.0 ,BOX_HEIGHT ,-BOX_WIDTH/2.0};
	GLdouble Point7[] = {BOX_WIDTH/2.0 ,BOX_HEIGHT ,-BOX_WIDTH/2.0};

    //glColor3f(0.56, 0.28, 0.08);
    glColor3f(240./255, 223./255, 167./255);

    glBegin(GL_POLYGON);
	glVertex3dv(Point0);
	glVertex3dv(Point1);
	glVertex3dv(Point2);
	glVertex3dv(Point3);
	glEnd();

    glColor3f(224./255, 206./255, 156./255);

    glBegin(GL_POLYGON);
	glVertex3dv(Point6);
	glVertex3dv(Point7);
	glVertex3dv(Point3);
	glVertex3dv(Point2);
	glEnd();
    
    glColor3f(240./255, 220./255, 167./255);


    glBegin(GL_POLYGON);
	glVertex3dv(Point5);
	glVertex3dv(Point6);
	glVertex3dv(Point2);
	glVertex3dv(Point1);
	glEnd();


    glBegin(GL_POLYGON);
	glVertex3dv(Point4);
	glVertex3dv(Point7);
	glVertex3dv(Point3);
	glVertex3dv(Point0);
	glEnd();

}

void SceneGame::checkGameOver(){
    for(const auto& item: fruits){
        if(item.second->getY() > BOX_HEIGHT + GAME_OVER_OFFSET_Y){
            gameOver = true;
            break;
        }
    }
}