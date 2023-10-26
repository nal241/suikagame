#include "gameObject.h"

const double Fruit::fruit_color[][3] = {{0,0,1}, {0,1,0}, {1,0,0}, {1, 1, 0}, {0,1,1}};
const double Fruit::fruit_radius[] = {1, 2, 3, 4, 5};

Fruit::Fruit(double x, double y, double z, int id)
{
    this->x = x; this->y = y; this->z = z;

    visible = true;
    object_type = 1;
    fruit_name = 0;
}

void Fruit::draw(){
    glPushMatrix();
    glMultMatrixf(m);
    glColor3d(fruit_color[fruit_name][0], fruit_color[fruit_name][1], fruit_color[fruit_name][2]);
    glutSolidSphere(fruit_radius[fruit_name], 50, 50);
    glPopMatrix();
}

