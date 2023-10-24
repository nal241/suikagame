#pragma once

#include "AbstractScene.h"

class SceneStart: public AbstractScene
{
public:
    SceneStart(Parameter& param, void (* changeScenePtr)(const eScene, Parameter&, const bool));
    virtual ~SceneStart() = default;
    void display();
    void update();
};