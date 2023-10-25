#pragma once

#include "AbstractScene.h"

class SceneGame: public AbstractScene
{
public:
    const static char* ParameterTestTag;


    SceneGame(Parameter& param, void (* changeScenePtr)(const eScene, Parameter&, const bool));
    virtual ~SceneGame() = default;
    void display();
    void update();

private:
    int testParameter;
};