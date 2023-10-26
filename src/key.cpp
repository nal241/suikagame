#include "key.h"

bool keyboard::key_state[KEY_SIZE] = {0};

void keyboard::initKeyBoard(){
    glutKeyboardFunc(keyBoardFunc);
    glutKeyboardUpFunc(keyBoardUpFunc);
    glutIgnoreKeyRepeat(GL_TRUE);
}

void keyboard::clearKeyState(){
    for(int i = 0; i < KEY_SIZE; i++){
        key_state[i] = false;
    }
}