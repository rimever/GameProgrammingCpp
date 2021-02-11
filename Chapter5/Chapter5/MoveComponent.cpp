#include "MoveComponent.h"


#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
	: Component(owner, updateOrder), mAngularSpeed(0.0f), mForwardSpeed(0.0f)
{
}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(this->mAngularSpeed))
	{
		auto rotation = this->mOwner->GetRotation();
		rotation += this->mAngularSpeed * deltaTime;
		this->mOwner->SetRotation(rotation);
	}
	if (!Math::NearZero(this->mForwardSpeed))
	{
		auto position = this->mOwner->GetPosition();
		position += this->mOwner->GetForward() * this->mForwardSpeed * deltaTime;
		if (position.x < -512.0f) { position.x = 510.0f; }
		else if (position.x > 512.0f) { position.x = -510.0f; }
		if (position.y < -384.0f) { position.y = 382.0f; }
		else if (position.y > 384.0f) { position.y = -382.0f; }
		this->mOwner->SetPosition(position);
	}
}
