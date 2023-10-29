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
    const double getY() const{
        return y;
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
    static const int MAX_FRUIT_NAME_TYPE;
    Fruit(double x, double y, double z, int id);
    Fruit(double x, double y, double z, int id, int fruit_name);
    void draw();
    const double getRadius() const{
        return fruit_radius[fruit_name];
    }
    const float* getColor() const{
        return fruit_color[fruit_name];
    }
    void stepUp();
    const int getFruitName() const{
        return fruit_name;
    }
    static const double getRadius(int _fruit_name){
        return fruit_radius[_fruit_name];
    }
    static const float* getColor(int _fruit_name){
        return fruit_color[_fruit_name];
    }
private:

    static const float fruit_color[][4];
    static const double fruit_radius[];
    int fruit_name;
};

