#include <memory>
#include "gameObject.h"
   
class Player{
public:
    Player() = default;
    Player(double _x, double _y, double _z);
    int falling = 0;
    int visible = 1;
    int fruitValid = 0;
    double x = 0;
    double y = 22;
    double z = 0;
    std::shared_ptr<Fruit> fruit;

    void updatePosition();
    inline void setPosition(double _x, double _y, double _z);
};

void Player::setPosition(double _x, double _y, double _z){
    x = _x;
    y = _y;
    z = _z;
}