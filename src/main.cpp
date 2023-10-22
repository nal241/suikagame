#include "main.h"
#include "define.h"
#include "callbackFunc.h"


int main(int argc, char *argv[]){
    init_GL(argc, argv);
    set_callback_functions();
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

}

