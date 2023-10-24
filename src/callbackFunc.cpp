#include "callbackFunc.h"
#include <GL/glut.h>
#include <stdlib.h>

void set_callback_functions(){
    glutKeyboardFunc(glut_keyboard);
}

void glut_keyboard(unsigned char key, int x, int y){
    if(key == 'q'){
        exit(0);
    }
}