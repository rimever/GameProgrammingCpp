#pragma once
#include <cstdint>
#include <vector>


#include "Math.h"

class Actor
{
public:
	enum State { EActive, EPaused, EDead };
	Actor(class Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime) {}

	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState) {}

	const Vector3& GetPosition() const { return mPosition; }
	void SetPosition(const Vector3& position) { mPosition = position; mRecomputeWorldTransform = true; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	const Quaternion& GetRotation() const { return mRotation; }
	void SetRotation(const Quaternion& rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }
	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	class Game* GetGame() const { return mGame; }
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	class Game* mGame;
	State mState;
	Matrix4 mWorldTransform;
	Quaternion mRotation;
	bool mRecomputeWorldTransform;
	float mScale;
	Vector3 mPosition;
	std::vector<class Component*> mComponents;
};

