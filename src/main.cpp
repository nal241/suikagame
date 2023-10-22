#include <GL/glut.h>

void init_GL(int argc, char *argv[]);
void init();

void display();


int main(int argc, char *argv[]){
    init_GL(argc, argv);

    glutMainLoop();
}

void init_GL(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("test");
}