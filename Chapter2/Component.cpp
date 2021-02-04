//
// Created on 2021/02/03.
//

#include "Component.h"
#include "Actor.h"

Component::Component(Actor *owner, int updateOrder)
        : mOwner(owner), mUpdateOrder(updateOrder) {
    this->mOwner->AddComponent(this);
}

Component::~Component() {
    this->mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime) {

}