#include "sceneGame.h"

#include <GL/glut.h>
#include <string>

#include "eScene.h"

const char* SceneGame::ParameterTestTag = "test";

SceneGame::SceneGame(Parameter& param, void (* changeScenePtr)(const eScene, Parameter&, const bool)):AbstractScene(param, changeScenePtr)
{
	testParameter = param.get(ParameterTestTag);
}

void SceneGame::display(){
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
    std::string str = "game: " + std::to_string(testParameter);

    glRasterPos2f(10, 10);
    int size = (int)str.size();
    for(int i = 0; i < size; ++i){
        char ic = str[i];
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ic);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
    

}

void SceneGame::update(){
    static int i = 0;
    if (i == 500){
      i = 0;
      Parameter param;
      changeScene(SCENE_START, param, 1);
    }
    i++;
    glutPostRedisplay();
}