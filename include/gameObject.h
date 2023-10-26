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
    const int getId() const{
        return id;
    }
    btRigidBody* body;
    GLfloat m[16];

protected:
    int id;
    bool visible;
    int object_type;
    double x;
    double y;
    double z;

};

class Fruit: public GameObject
{
public:
    static const int MAX_FRUIT_NAME_SIZE;
    Fruit(double x, double y, double z, int id);
    void draw();
    const double getRadius() const{
        return fruit_radius[fruit_name];
    }
    void stepUp();
    const int getFruitName() const{
        return fruit_name;
    }
private:

    static const double fruit_color[][3];
    static const double fruit_radius[];
    int fruit_name;
};

