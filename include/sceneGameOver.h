#pragma once

#include "AbstractScene.h"

class SceneGameOver: public AbstractScene
{
public:
    SceneGameOver(Parameter& param, void (* changeScenePtr)(const eScene, Parameter&, const bool));
    virtual ~SceneGameOver() = default;
    void display();
    void update();

    const static char* ResultTag;
    int result;
};