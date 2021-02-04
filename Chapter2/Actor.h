//
// Created on 2021/02/03.
//

#ifndef CHAPTER2_ACTOR_H
#define CHAPTER2_ACTOR_H


#pragma once

#include <vector>
#include "Math.h"


class Actor {
public:
    enum State {
        EActive,
        EPaused,
        EDead
    };

    Actor(class Game *game);

    virtual ~Actor();

    void UpdateComponents(float deltaTime);

    void Update(float deltaTime);

    virtual void UpdateActor(float deltaTime);

    void RemoveComponent(class Component *component);

    void AddComponent(class Component *component);

    const Vector2 &GetPosition() const { return this->mPosition; }

    void SetPosition(const Vector2 &pos) { this->mPosition = pos; }

    float GetScale() const { return this->mScale; }

    void SetScale(float scale) { this->mScale = scale; }

    float GetRotation() const { return this->mRotation; }

    void SetRotation(float rotation) { this->mRotation = rotation; }

    State GetState() const { return this->mState; }

    void SetState(State state) { this->mState = state; }

    class Game *GetGame() { return this->mGame; }

private:
    State mState;
    Vector2 mPosition;
    float mScale;
    float mRotation;

    class Game *mGame;

    std::vector<class Component *> mComponents;
};


#endif //CHAPTER2_ACTOR_H
