#pragma once
#include "eScene.h"

void glut_timer(int value);
void glut_display();


class Parameter;
void changeScene(const eScene scene, Parameter& parameter, const bool stackClear);

void initScene();