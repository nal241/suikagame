#include "gameLoop.h"

#include <stack>
#include <memory>
#include <GL/glut.h>

#include "scenes.h"
#include "key.h"


static std::stack<std::shared_ptr<AbstractScene>> sceneStack;


void glut_timer(int value){
    sceneStack.top()->update();

    glutTimerFunc(1000.f / 60.f, glut_timer, 0);
}

void glut_display(){
    sceneStack.top()->display();
}


void changeScene(const eScene scene, Parameter& parameter, const bool stackClear){
    printf("changed\n");
    keyboard::clearKeyState();
    if(stackClear){
        while (!sceneStack.empty()){
            sceneStack.pop();
        }
    }
    switch (scene){
        case SCENE_START:
            sceneStack.push(std::make_shared<SceneStart>(parameter, changeScene));
            break;
        case SCENE_GAME:
            sceneStack.push(std::make_shared<SceneGame>(parameter, changeScene));
            break;
        case SCENE_GAME_OVER:
            sceneStack.push(std::make_shared<SceneGameOver>(parameter, changeScene));
            break;
        case SCENE_GAME_PAUSE:
            sceneStack.push(std::make_shared<SceneGamePause>(parameter, changeScene));
            break;
        case SCENE_BACK:
            sceneStack.pop();
            if(sceneStack.empty()){fprintf(stderr, "scenge change error: empty scene\n"); exit(1);}
            break;
        default:
            break;
    }

}

void initScene(){
    Parameter parameter;
    changeScene(SCENE_START, parameter, true);
}