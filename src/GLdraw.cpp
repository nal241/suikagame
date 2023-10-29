#include "GLdraw.h"


void drawSquare(GLdouble x, GLdouble y, GLdouble height){
    GLdouble Point0[] = {x, y, height};
	GLdouble Point1[] = {x, -y, height};
	GLdouble Point2[] = {-x, -y, height};
	GLdouble Point3[] = {-x, y, height};

	glBegin(GL_POLYGON);
	glVertex3dv(Point0);
	glVertex3dv(Point1);
	glVertex3dv(Point2);
	glVertex3dv(Point3);
	glEnd();

}

void drawString(std::string& str, int x, int y){
    glRasterPos2f(x, y);
    for(size_t i = 0; i < str.size(); i++){
        char ic = str[i];
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ic);
    }

}