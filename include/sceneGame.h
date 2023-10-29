#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <random>

#include "AbstractScene.h"
#include "gameObject.h"
#include "key.h"
#include "gamePlayer.h"


class SceneGame: public AbstractScene
{
public:
    const static char* ParameterTestTag;


    SceneGame(Parameter& param, void (* changeScenePtr)(const eScene, Parameter&, const bool));
    virtual ~SceneGame() = default;
    void display();
    void update();
    const bool isGameOver()const{
        return gameOver;
    }

private:
    const int MIN_FRUIT_NAME = 0;
    const int MAX_FRUIT_NAME = 4;
    const double BOX_WIDTH = 10;
    const double BOX_HEIGHT = 13; 

    //オフセット
    const float GAME_OVER_OFFSET_Y = 1;
    const float PLAYER_FROM_BOX_HEIGHT = 2;
    const float PLAYER_MOVABLE_WIDTH = 1;



    int testParameter;
    int object_id = 1;
    int key_available[KEY_SIZE] = {0};

    int score = 0;

    int current_fruit_name;
    int next_fruit_name;
    std::shared_ptr<Fruit> next_fruit;

    bool gameOver = false;
    

    Player player;
    

    std::mt19937 random;


    std::unordered_map<int, std::shared_ptr<GameObject>> objects;
    std::unordered_map<int, std::shared_ptr<Fruit>> fruits;

    Physics physics;

    int mergeFruit(int idA, int idB, btVector3 Point);
    void initStage();
    void drawStage();
    void checkGameOver();
    void displayUI();
};