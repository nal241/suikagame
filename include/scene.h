#pragma once

typedef enum {
    SCENE_START,
    SCENE_GAME,
    SCENE_MAX
} eScene;

static unsigned char key[256];

class manageScene{
public:
    void changeScene(eScene s);
private:

};

class scene{
public:
    virtual void displayFunc() = 0;
};
