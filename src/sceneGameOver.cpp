#include "sceneGameOver.h"

#include <GL/glut.h>
#include <string>

#include "eScene.h"
#include "key.h"
#include "GLdraw.h"
#include "define.h"

const char* SceneGameOver::ResultTag = "ResultTag"; 

SceneGameOver::SceneGameOver(Parameter& param, void (* changeScenePtr)(const eScene, Parameter&, const bool)):AbstractScene(param, changeScenePtr)
{
    glClearColor(0.7765, 0.5568, 0.3176, 0.0);

    result = param.get(ResultTag);
}

void SceneGameOver::display(){
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0 , WINDOW_X, WINDOW_Y, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //square

    glColor3f(1.0, 201./255, 115./255);
    glBegin(GL_POLYGON);
    glVertex2f(WINDOW_X * 0.2, WINDOW_Y*0.2);
    glVertex2f(WINDOW_X * 0.2, WINDOW_Y*0.8);
    glVertex2f(WINDOW_X * 0.8, WINDOW_Y*0.8);
    glVertex2f(WINDOW_X * 0.8, WINDOW_Y*0.2);
    glEnd();

    // 画面上にテキスト描画
    glColor3f(1.0, 1.0, 1.0);
    std::string str = "Game Over";
    drawString(str, 580, 220);

    str = "Score:";
    str += std::to_string(result);
    drawString(str, 580, 350);
    str = "1: RETRY";
    drawString(str, 580, 450);
    str = "2: TITLE";
    drawString(str, 580, 500);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();

}

void SceneGameOver::update(){
    if(keyboard::getKeyState('1')){
        Parameter param;
        changeScene(SCENE_GAME, param, 1);
    }
    if(keyboard::getKeyState('2'))
    {
        Parameter param;
        changeScene(SCENE_START, param, 1);
    }
}