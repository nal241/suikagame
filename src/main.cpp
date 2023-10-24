#include "main.h"
#include "define.h"
#include "callbackFunc.h"
#include "Utils.h"
#include <GL/glut.h>


int main(int argc, char *argv[]){
    init_GL(argc, argv);
    init();
    glutMainLoop();

    return 0;
}

void init_GL(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_X, WINDOW_Y);
    glutCreateWindow(WINDOW_NAME);
}

void init(){
    set_callback_functions();
    keyboard::initKeyBoard();
}

