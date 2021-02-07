//
// Created on 2021/02/07.
//

#include "AIComponent.h"
#include "Actor.h"
#include "AIState.h"
#include "SDL_log.h"

AIComponent::AIComponent(class Actor *owner) : Component(owner), mCurrentState(nullptr) {

}

void AIComponent::Update(float deltaTime) {
    if (this->mCurrentState) {
        this->mCurrentState->Update(deltaTime);
    }
}

void AIComponent::ChangeState(const std::string &name) {
    if (this->mCurrentState) {
        this->mCurrentState->OnExit();
    }
    auto iter = mStateMap.find(name);
    if (iter != this->mStateMap.end()) {
        this->mCurrentState = iter->second;
        this->mCurrentState->OnEnter();
    } else {
        SDL_Log("Could not find AIState %s in state map", name.c_str());
        this->mCurrentState = nullptr;
    }
}

void AIComponent::RegisterState(class AIState* state) {
    this->mStateMap.emplace(state->GetName(), state);
}