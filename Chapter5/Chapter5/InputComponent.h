#pragma once
#include "MoveComponent.h"

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);
	void ProcessInput(const uint8_t* keyState) override;
	float GetMaxForward() const { return this->mMaxForwardSpeed; }
	float GetMaxAngular() const { return this->mMaxAngularSpeed; }
	int GetForwardKey() const { return this->mForwardKey; }
	int GetBackKey() const { return this->mBackKey; }
	int GetClockwiseKey() const { return this->mClockwiseKey; }
	int GetCounterClockwiseKey() const { return this->mCounterClockwiseKey; }

	void SetMaxForwardSpeed(float speed) { this->mMaxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { this->mMaxAngularSpeed = speed; }
	void SetForwardKey(int key) { this->mForwardKey = key; }
	void SetBackKey(int key) { this->mBackKey = key; }
	void SetClockwiseKey(int key) { this->mClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { this->mCounterClockwiseKey = key; }
private:
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	int mForwardKey;
	int mBackKey;
	int mClockwiseKey;
	int mCounterClockwiseKey;
};
