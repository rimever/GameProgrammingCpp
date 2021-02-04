//
// Created on 2021/02/04.
//

#ifndef CHAPTER3_ASTEROID_H
#define CHAPTER3_ASTEROID_H


#include "Actor.h"

class Asteroid: public Actor {
public:
    Asteroid(class Game* game);
    ~Asteroid();

    class CircleComponent* GetCircle() { return this->mCircle;}

private:
    class CircleComponent* mCircle;
};


#endif //CHAPTER3_ASTEROID_H
