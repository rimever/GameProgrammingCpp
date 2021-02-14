#include "CircleComponent.h"

#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner)
	:Component(owner),mRadius(0.0f){
}

const Vector3& CircleComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	auto diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;
	return distSq <= radiiSq;
}

float CircleComponent::GetRadius() const
{
	return mOwner->GetScale() * mRadius;
}



