#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "AbstractScene.h"
#include "gameObject.h"


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

    std::unordered_map<int, std::shared_ptr<GameObject>> objects;
    std::unordered_map<int, std::shared_ptr<Fruit>> fruits;

    Physics physics;
};