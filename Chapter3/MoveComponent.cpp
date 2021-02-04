//
// Created on 2021/02/04.
//

#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor *owner, int updateOrder)
        : Component(owner, updateOrder), mAngularSpeed(0.0f), mForwardSpeed(0.0f) {}

void MoveComponent::Update(float deltaTime) {
    if (!Math::NearZero(mAngularSpeed)) {
        float rot = this->mOwner->GetRotation();
        rot += this->mAngularSpeed * deltaTime;
        this->mOwner->SetRotation(rot);
    }

    if (!Math::NearZero(this->mForwardSpeed)) {
        Vector2 pos = mOwner->GetPosition();
        pos += this->mOwner->GetForward() * this->mForwardSpeed * deltaTime;

        if (pos.x < 0.0f) { pos.x = 1022.0f; }
        else if (pos.x > 1024.f) { pos.x = 2.0f; }

        if (pos.y < 0.0f) { pos.y = 766.0f; }
        else if (pos.y > 768.0f) { pos.y = 2.0f; }
        this->mOwner->SetPosition(pos);
    }
}