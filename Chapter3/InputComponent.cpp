//
// Created on 2021/02/04.
//

#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor *owner)
        :MoveComponent(owner)
        ,mForwardKey(0)
        ,mBackKey(0)
        ,mClockwiseKey(0)
        ,mCounterClockwiseKey(0){

}

void InputComponent::ProcessInput(const uint8_t *keyState) {
    float forwardSpeed = 0.0f;
    if (keyState[this->mForwardKey]) {
        forwardSpeed += this->mMaxForwardSpeed;
    }
    if (keyState[this->mBackKey]) {
        forwardSpeed -= this->mMaxForwardSpeed;
    }
    SetForwardSpeed(forwardSpeed);

    float angularSpeed = 0.0f;
    if (keyState[mClockwiseKey]) {
        angularSpeed += this->mMaxAngularSpeed;
    }
    if (keyState[mCounterClockwiseKey]) {
        angularSpeed -= this->mMaxAngularSpeed;
    }
    SetAngularSpeed(angularSpeed);
}
