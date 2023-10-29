#include "gameObject.h"

const int Fruit::MAX_FRUIT_NAME_TYPE = 11;
const float Fruit::fruit_color[][4] = {
    {0.8549, 0.0235, 0.0157 ,1}, {1.0, 0.5411, 0.4157 ,1}, {0.6156, 0.3333, 0.9607 ,1}, {1.0, 0.6901, 0.0078,1}, {1.0, 0.5176, 0.0980 ,1},
    {0.9490, 0.0549, 0.0470,1}, {0.9803, 0.9215, 0.4824,1}, {1.0, 0.8117, 0.7804,1}, {0.9843, 0.8863, 0.0431,1}, {0.5412, 0.8157, 0.0667,1},
    {0.0588, 0.4980, 0.0275,1}};
const double Fruit::fruit_radius[] = {0.5, 0.8, 1.1, 1.4, 1.7, 2.0, 2.3, 2.6, 2.9, 3.2, 3.5};

Fruit::Fruit(double x, double y, double z, int id)
{
    this->x = x; this->y = y; this->z = z;

    visible = true;
    object_type = 1;
    fruit_name = 0;
    this->id = id;
}

Fruit::Fruit(double x, double y, double z, int id, int fruit_name){
    this->x = x; this->y = y; this->z = z;

    visible = true;
    object_type = 1;
    this->fruit_name = fruit_name;
    this->id = id;    
}

void Fruit::draw(){
    glPushMatrix();
    glColor3d(fruit_color[fruit_name][0], fruit_color[fruit_name][1], fruit_color[fruit_name][2]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, fruit_color[fruit_name]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, fruit_color[fruit_name]);
    glMultMatrixf(m);
    glutSolidSphere(fruit_radius[fruit_name], 50, 50);
    glPopMatrix();
}

void Fruit::stepUp(){
    if(fruit_name < MAX_FRUIT_NAME_TYPE)fruit_name++;
}