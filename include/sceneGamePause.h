#pragma once

#include "AbstractScene.h"

class SceneGamePause: public AbstractScene
{
public:
    SceneGamePause(Parameter& param, void (* changeScenePtr)(const eScene, Parameter&, const bool));
    void display();
    void update();

    const static char* ResultTag;
    int result;
};