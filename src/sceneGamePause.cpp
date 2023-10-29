#include "sceneGamePause.h"

#include <GL/glut.h>
#include <string>

#include "eScene.h"
#include "key.h"
#include "GLdraw.h"
#include "define.h"


SceneGamePause::SceneGamePause(Parameter& param, void (* changeScenePtr)(const eScene, Parameter&, const bool)):AbstractScene(param, changeScenePtr)
{
    glClearColor(0.7765, 0.5568, 0.3176, 0.0);
}

void SceneGamePause::display(){
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
    std::string str = "PAUSE";
    drawString(str, 580, 220);

    str = "1: RESUME";
    drawString(str, 580, 450);
    str = "2: TITLE";
    drawString(str, 580, 500);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();

}

void SceneGamePause::update(){
    if(keyboard::getKeyState('1')){
        Parameter param;
        //changeScene(SCENE_GAME, param, 1);
        changeScene(SCENE_BACK, param, 0);
    }
    if(keyboard::getKeyState('2'))
    {
        Parameter param;
        changeScene(SCENE_START, param, 1);
    }
}