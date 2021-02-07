//
// Created on 2021/02/05.
//

#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor *owner, int updateOrder)
        : Component(owner, updateOrder), mAngularSpeed(0.0f), mForwardSpeed(0.0f) {

}

void MoveComponent::Update(float deltaTime) {
    if (!Math::NearZero(this->mAngularSpeed)) {
        float rot = this->mOwner->GetRotation();
        rot += this->mAngularSpeed * deltaTime;
        this->mOwner->SetRotation(rot);
    }

    if (!Math::NearZero(this->mForwardSpeed)) {
        Vector2 pos = this->mOwner->GetPosition();
        pos += this->mOwner->GetForward() * this->mForwardSpeed * deltaTime;
        this->mOwner->SetPosition(pos);
    }
}