#pragma once

#include <GL/glut.h>
#include <stdio.h>
#define KEY_SIZE (256)

class keyboard{
public:
    static void keyBoardFunc(unsigned char key, int x, int y){
        key_state[key] = true;
    }

    static void keyBoardUpFunc(unsigned char key, int x, int y){
        key_state[key] = false;
    }

    static bool getKeyState(unsigned char key){
        return key_state[key];
    }

    static void initKeyBoard();
private:
    static bool key_state[KEY_SIZE];
};



