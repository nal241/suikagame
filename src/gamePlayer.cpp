#include "gamePlayer.h"

Player::Player(double _x, double _y, double _z){
    x = _x; y = _y; z = _z;
}

void Player::updatePosition(){
    double _m[16] = {1,0,0,0,0,1,0,0,0,0,1,0,x,y,z,1};
    for(int i = 0; i < 16; i++){
        fruit->m[i] = _m[i];
    }
}
