//
// Created on 2021/02/04.
//

#ifndef CHAPTER3_LASER_H
#define CHAPTER3_LASER_H

#include "Actor.h"

class Laser: public Actor {
public:
    Laser(class Game* game);
    void UpdateActor(float deltaTime) override;

private:
    class CircleComponent* mCircle;
    float mDeathTimer;
};


#endif //CHAPTER3_LASER_H
