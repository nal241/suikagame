#include "init.h"
#include "define.h"
#include "callbackFunc.h"
#include "gameLoop.h"


#include <GL/glut.h>



void init_GL(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_X, WINDOW_Y);
    glutCreateWindow(WINDOW_NAME);
}

void init(){
    set_callback_functions();
    //keyboard::initKeyBoard();
    initScene();
}

