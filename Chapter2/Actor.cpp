//
// Created on 2021/02/03.
//

#include <algorithm>
#include "Actor.h"
#include "Game.h"
#include "Component.h"

void UpdateComponents(float deltaTime);

Actor::Actor(Game *game)
        : mState(EActive), mPosition(Vector2::Zero), mScale(1.f), mRotation(0.f), mGame(game) {
    mGame->AddActor(this);
}

Actor::~Actor() {
    this->mGame->RemoveActor(this);
    while (!this->mComponents.empty()) {
        delete this->mComponents.back();
    }
}

void Actor::Update(float deltaTime) {
    if (this->mState == EActive) {
        this->UpdateComponents(deltaTime);
        this->UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime) {
    for (auto comp : this->mComponents) {
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime) {

}

void Actor::AddComponent(Component *component) {
    int myOrder = component->GetUpdateOrder();
    auto iter = this->mComponents.begin();
    for (; iter != this->mComponents.end(); ++iter) {
        if (myOrder < (*iter)->GetUpdateOrder()) {
            break;
        }
    }
    this->mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component *component) {
    auto iter = std::find(this->mComponents.begin(), this->mComponents.end(), component);
    if (iter != this->mComponents.end()) {
        this->mComponents.erase(iter);
    }
}

