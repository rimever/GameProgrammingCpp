#include "MoveComponent.h"


#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
	:Component(owner,updateOrder)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
{
}

void MoveComponent::Update(float deltaTime)
{
		if (!Math::NearZero(mAngularSpeed))
	{
		auto rotation = mOwner->GetRotation();
		float angle = mAngularSpeed * deltaTime;
		Quaternion inc(Vector3::UnitZ,angle);
		rotation = Quaternion::Concatenate(rotation,inc);
		mOwner->SetRotation(rotation);
	}
	if (!Math::NearZero(mForwardSpeed))
	{
		auto position = mOwner->GetPosition();
		position += mOwner->GetForward() * mForwardSpeed * deltaTime;
		mOwner->SetPosition(position);
	}
}

