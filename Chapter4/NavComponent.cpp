//
// Created on 2021/02/05.
//

#include "NavComponent.h"
#include "Tile.h"

NavComponent::NavComponent(class Actor *owner, int updateOrder) : MoveComponent(owner, updateOrder),
                                                                  mNextNode(nullptr) {

}

void NavComponent::Update(float deltaTime) {
    if (this->mNextNode) {
        Vector2 diff = this->mOwner->GetPosition() - this->mNextNode->GetPosition();
        if (Math::NearZero(diff.Length(), 2.0f)) {
            this->mNextNode = this->mNextNode->GetParent();
            TurnTo(this->mNextNode->GetPosition());
        }
    }
    MoveComponent::Update(deltaTime);
}

void NavComponent::StartPath(const class Tile *start) {
    this->mNextNode = start->GetParent();
    TurnTo(this->mNextNode->GetPosition());
}

void NavComponent::TurnTo(const Vector2 &pos) {
    Vector2 dir = pos - this->mOwner->GetPosition();
    float angle = Math::Atan2(-dir.y, dir.x);
    this->mOwner->SetRotation(angle);
}