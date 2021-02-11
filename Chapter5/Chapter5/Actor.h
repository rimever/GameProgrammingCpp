#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from Game(not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// ProcessInput function called from Game (not overridable)
	void ProcessInput(const uint8_t* keyState);
	// Any actor-specific input code(overridable)
	virtual void ActorInput(const uint8_t* keyState);

	// Getters/Setters
	const Vector2& GetPosition() const { return this->mPosition; }

	void SetPosition(const Vector2& position)
	{
		this->mPosition = position;
		this->mRecomputeWorldTransform = true;
	}

	float GetScale() const { return this->mScale; }
	void SetScale(float scale) { this->mScale = scale; }
	float GetRotation() const { return this->mRotation; }

	void SetRotation(float rotation)
	{
		this->mRotation = rotation;
		this->mRecomputeWorldTransform = true;
	}

	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return this->mWorldTransform; }

	Vector2 GetForward() const { return Vector2(Math::Cos(this->mRotation), Math::Sin(this->mRotation)); }

	State GetState() const { return this->mState; }
	void SetState(State state) { this->mState = state; }

	class Game* GetGame() { return this->mGame; }

	// Add Components
	void AddComponent(class Component* component);
	// Remove Components
	void RemoveComponent(class Component* component);
private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation;
	Game* mGame;
	Matrix4 mWorldTransform;
	bool mRecomputeWorldTransform;
	std::vector<class Component*> mComponents;
};
