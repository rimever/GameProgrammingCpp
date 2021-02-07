//
// Created on 2021/02/05.
//

#ifndef CHAPTER4_ACTOR_H
#define CHAPTER4_ACTOR_H

#include <vector>
#include "Math.h"
#include <stdint.h>

class Actor {
public:
    enum State {
        EActive,
        EPaused,
        EDead
    };

    Actor(class Game *game);

    virtual ~Actor();

    void Update(float deltaTime);

    void UpdateComponents(float deltaTime);

    virtual void UpdateActor(float deltaTime);

    void ProcessInput(const u_int8_t *keyState);

    virtual void ActorInput(const u_int8_t *keyState);

    const Vector2 &GetPosition() const { return this->mPosition; }

    void SetPosition(const Vector2 &pos) { this->mPosition = pos; }

    float GetScale() const { return this->mScale; }

    void SetScale(float scale) { this->mScale = scale; }

    float GetRotation() const { return this->mRotation; }

    void SetRotation(float rotation) { this->mRotation = rotation; }

    Vector2 GetForward() const { return Vector2(Math::Cos(this->mRotation), -Math::Sin(this->mRotation)); }

    State GetState() const { return this->mState; }

    void SetState(State state) { this->mState = state; }

    class Game *GetGame() { return this->mGame; }

    void AddComponent(class Component *component);

    void RemoveComponent(class Component *component);

private:
    Vector2 mPosition;
    float mScale;
    float mRotation;
    State mState;
    std::vector<class Component *> mComponents;

    class Game *mGame;
};


#endif //CHAPTER4_ACTOR_H
