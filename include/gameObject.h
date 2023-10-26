#pragma once
#include <GL/glut.h>

#include "physics.h"

class GameObject
{
public:
    virtual void draw() = 0;
    virtual void setPosition(double x, double y, double z){
    this->x = x; this->y = y; this->z = z;
}
    int id;
    bool visible;
    int object_type;
    double x;
    double y;
    double z;

    btRigidBody* body;
    GLfloat m[16];
};

class Fruit: public GameObject
{
public:
    Fruit(double x, double y, double z, int id);
    void draw();
    const double getRadius() const{
        return fruit_radius[fruit_name];
    }
private:
    static const double fruit_color[][3];
    static const double fruit_radius[];
    int fruit_name;
};

