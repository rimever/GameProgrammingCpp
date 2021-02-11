#include "CircleComponent.h"

#include "Actor.h"

class Vector2;

CircleComponent::CircleComponent(Actor* owner)
	: Component(owner), mRadius(0.0f)
{
}

float CircleComponent::GetRadius() const
{
	return this->mOwner->GetScale() * this->mRadius;
}

const Vector2& CircleComponent::GetCenter() const
{
	return this->mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	auto diff = a.GetCenter() - b.GetCenter();
	auto distSq = diff.LengthSq();

	auto radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}
