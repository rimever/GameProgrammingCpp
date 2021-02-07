//
// Created on 2021/02/05.
//

#ifndef CHAPTER4_BULLET_H
#define CHAPTER4_BULLET_H

#include "Actor.h"

class Bullet : public Actor{
public:
    Bullet(class Game* game);
    void UpdateActor(float deltaTime) override;

private:
    class CircleComponent* mCircle;
    float mLiveTime;
};


#endif //CHAPTER4_BULLET_H
