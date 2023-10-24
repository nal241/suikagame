#include "callbackFunc.h"
#include "gameLoop.h"
#include <GL/glut.h>
#include <stdlib.h>


void set_callback_functions(){
    glutKeyboardFunc(glut_keyboard);
    glutTimerFunc(1000.f/ 60.f, glut_timer, 0);
    glutDisplayFunc(glut_display);
}

void glut_keyboard(unsigned char key, int x, int y){
    if(key == 'q'){
        exit(0);
    }
}


