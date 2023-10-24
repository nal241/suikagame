#include "gameLoop.h"

//#include "Utils.h"
#include "scenes.h"
#include <stack>
#include <memory>

#include <GL/glut.h>

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
        default:
            break;
    }

}

void initScene(){
    Parameter parameter;
    changeScene(SCENE_START, parameter, true);
}