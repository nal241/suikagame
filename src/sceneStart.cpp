#include "sceneStart.h"

#include <GL/glut.h>
#include <string>

#include "eScene.h"
#include "sceneGame.h"
#include "key.h"
#include "GLdraw.h"


SceneStart::SceneStart(Parameter& param, void (* changeScenePtr)(const eScene, Parameter&, const bool)):AbstractScene(param, changeScenePtr)
{
    glClearColor(0.7765, 0.5568, 0.3176, 0.0);
}

void SceneStart::display(){
  	glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    // 平行投影にする
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1280, 720, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // 画面上にテキスト描画
    std::string str = "Fruit Game";
    drawString(str, 580, 150);

    str = "1: START";
    drawString(str, 580, 450);
    str = "2: QUIT";
    drawString(str, 580, 500);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
    


}

void SceneStart::update(){
    /*
	static int i = 0;
	if (i == 500){
	i = 0;
	Parameter param;
    param.set(SceneGame::ParameterTestTag, 125);
	changeScene(SCENE_GAME, param, 1);
	}
	i++;*/
    if(keyboard::getKeyState('2')) exit(0);
    Parameter param;
    param.set(SceneGame::ParameterTestTag, 125);
    if(keyboard::getKeyState('1')) changeScene(SCENE_GAME, param, 1);

	glutPostRedisplay();
}