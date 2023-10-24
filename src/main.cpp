#include "main.h"
#include "init.h"
#include <GL/glut.h>


int main(int argc, char *argv[]){
    init_GL(argc, argv);
    init();
    glutMainLoop();

    return 0;
}

