

#ifndef CHAPTER2_SHIP_H
#define CHAPTER2_SHIP_H

#include "Actor.h"

class Ship : public Actor {

public:
    Ship(Game *game);

    void UpdateActor(float deltaTime) override;

    void ProcessKeyboard(const uint8_t *state);

    float GetRightSpeed() const { return this->mRightSpeed; }

    float GetDownSpeed() const { return this->mDownSpeed; }

private:
    float mRightSpeed;
    float mDownSpeed;
};

#endif //CHAPTER2_SHIP_H
