#pragma once
#include "sceneParameter.h"
#include "eScene.h"

class AbstractScene{
public:
    AbstractScene(Parameter& parameter, void (* changeScenePtr)(const eScene, Parameter&, const bool)):changeScene(changeScenePtr){};
    virtual ~AbstractScene() = default;
    virtual void update() = 0;
    virtual void display() = 0;

protected:
    void (* changeScene)(const eScene, Parameter&, const bool);
};

