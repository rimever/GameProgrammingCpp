//
// Created on 2021/02/06.
//

#ifndef CHAPTER4_TOWER_H
#define CHAPTER4_TOWER_H

#include "Actor.h"

class Tower : public Actor {
public:
    Tower(class Game *game);

    void UpdateActor(float deltaTime) override;

private:
    class MoveComponent *mMove;

    float mNextAttack;
    const float AttackTime = 2.5f;
    const float AttackRange = 100.0f;
};


#endif //CHAPTER4_TOWER_H
