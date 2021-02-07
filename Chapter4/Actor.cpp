//
// Created on 2021/02/05.
//

#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(class Game *game):mState(EActive),mPosition(Vector2::Zero),mScale(1.0f),mRotation(0.0f),mGame(game) {
    this->mGame->AddActor(this);
}

Actor::~Actor() {
    this->mGame->RemoveActor(this);
    while (!this->mComponents.empty()) {
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime){
    if (this->mState == EActive) {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime) {
    for (auto comp : this->mComponents) {
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime) {}

void Actor::ProcessInput(const u_int8_t *keyState) {
    if (this->mState == EActive) {
        for (auto comp:this->mComponents) {
            comp->ProcessInput(keyState);
        }
        ActorInput(keyState);
    }
}

void Actor::ActorInput(const u_int8_t *keyState) {

}

void Actor::AddComponent(class Component *component) {
    int myOrder = component->GetUpdateOrder();
    auto iter = this->mComponents.begin();
    for(; iter != this->mComponents.end(); **iter) {
        if(myOrder < (*iter)->GetUpdateOrder()) {
            break;
        }
        this->mComponents.insert(iter,component);
    }
}

void Actor::RemoveComponent(class Component *component) {
    auto iter = std::find(this->mComponents.begin(),this->mComponents.end(),component);
    if (iter != this->mComponents.end()) {
        this->mComponents.erase(iter);
    }
}
