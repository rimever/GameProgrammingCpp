//
// Created on 2021/02/04.
//

#ifndef CHAPTER3_SHIP_H
#define CHAPTER3_SHIP_H


#include "Actor.h"

class Ship : public Actor{
public:
    Ship(class Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const uint8_t* keyState) override;

private:
    float mLaserCooldown;
};


#endif //CHAPTER3_SHIP_H
