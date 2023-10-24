#include "callbackFunc.h"

void set_callback_functions(){
    glutKeyboardFunc(glut_keyboard);
    glutDisplayFunc(glut_display);
}

void glut_keyboard(unsigned char key, int x, int y){
    if(key == 'q'){
        exit(0);
    }
}

void glut_display(){
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(30.0, 1.0, 0.1, 100);
    //glDisable(GL_LIGHTING);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    gluOrtho2D(0, 1280, 720, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    std::string s1 = "test_test";
    glRasterPos2d(10, 10);
    glColor3d(0.0, 0.0, 1.0);
    for(size_t i = 0; i < s1.size(); i++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s1[i]);
    }

    glutSwapBuffers();
}