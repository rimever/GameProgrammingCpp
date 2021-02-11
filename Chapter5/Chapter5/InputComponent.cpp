#include "InputComponent.h"

InputComponent::InputComponent(Actor* owner): MoveComponent(owner), mForwardKey(0), mBackKey(0), mClockwiseKey(0),
                                              mCounterClockwiseKey(0)
{
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
    auto forwardSpeed = 0.0f;
    if (keyState[this->mForwardKey])
    {
        forwardSpeed += this->mMaxForwardSpeed;
    }
    if (keyState[this->mBackKey])
    {
        forwardSpeed -= this->mMaxForwardSpeed;
    }
    SetForwardSpeed(forwardSpeed);

    auto angularSpeed = 0.0f;
    if (keyState[this->mClockwiseKey])
    {
        angularSpeed += this->mMaxAngularSpeed;
    }
    if (keyState[this->mCounterClockwiseKey])
    {
        angularSpeed -= this->mMaxAngularSpeed;
    }
    SetAngularSpeed(angularSpeed);
}
