#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return this->mAngularSpeed; }
	float GetForwardSpeed() const { return this->mForwardSpeed; }
	void SetAngularSpeed(float speed) { this->mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { this->mForwardSpeed = speed; }
private:
	float mAngularSpeed;
	float mForwardSpeed;
};
