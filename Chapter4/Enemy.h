//
// Created on 2021/02/06.
//

#ifndef CHAPTER4_ENEMY_H
#define CHAPTER4_ENEMY_H


#include "Actor.h"

class Enemy : public Actor {
public:
    Enemy(class Game *game);

    ~Enemy();

    void UpdateActor(float deltaTime) override;

    class CircleComponent *GetCircle() { return this->mCircle; }

private:
    class CircleComponent *mCircle;
};


#endif //CHAPTER4_ENEMY_H
