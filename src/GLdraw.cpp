#include "GLdraw.h"

#include <GL/glut.h>

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