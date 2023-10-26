#include "gameObject.h"

const int Fruit::MAX_FRUIT_NAME_SIZE = 5;
const double Fruit::fruit_color[][3] = {{0,0,1}, {0,1,0}, {1,0,0}, {1, 1, 0}, {0,1,1}};
const double Fruit::fruit_radius[] = {0.5, 0.8, 1.1, 1.4, 1.7};

Fruit::Fruit(double x, double y, double z, int id)
{
    this->x = x; this->y = y; this->z = z;

    visible = true;
    object_type = 1;
    fruit_name = 0;
    this->id = id;
}

void Fruit::draw(){
    glPushMatrix();
    glMultMatrixf(m);
    glColor3d(fruit_color[fruit_name][0], fruit_color[fruit_name][1], fruit_color[fruit_name][2]);
    glutSolidSphere(fruit_radius[fruit_name], 50, 50);
    glPopMatrix();
}

void Fruit::stepUp(){
    if(fruit_name < MAX_FRUIT_NAME_SIZE)fruit_name++;
}