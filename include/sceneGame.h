#pragma once

#include "AbstractScene.h"

class SceneGame: public AbstractScene
{
public:
    SceneGame(Parameter& param, void (* changeScenePtr)(const eScene, Parameter&, const bool));
    virtual ~SceneGame() = default;
    void display();
    void update();
};