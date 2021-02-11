#include "Actor.h"


#include "Component.h"
#include "Game.h"
#include <algorithm>

Actor::Actor(Game* game)
	: mState(EActive)
	  , mPosition(Vector2::Zero)
	  , mScale(1.0f)
	  , mRotation(0.0f)
	  , mGame(game)
	  , mRecomputeWorldTransform(true)
{
	this->mGame->AddActor(this);
}

Actor::~Actor()
{
	this->mGame->RemoveActor(this);
	while (!this->mComponents.empty())
	{
		delete this->mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (this->mState == EActive)
	{
		ComputeWorldTransform();
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
		ComputeWorldTransform();
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto* component : this->mComponents)
	{
		component->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (this->mState == EActive)
	{
		for (auto* component : this->mComponents)
		{
			component->ProcessInput(keyState);
		}
		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t* keyState)
{
}

void Actor::ComputeWorldTransform()
{
	if (this->mRecomputeWorldTransform)
	{
		this->mRecomputeWorldTransform = false;
		this->mWorldTransform = Matrix4::CreateScale(this->mScale);
		this->mWorldTransform *= Matrix4::CreateRotationZ(this->mRotation);
		this->mWorldTransform *= Matrix4::CreateTranslation(Vector3(this->mPosition.x, this->mPosition.y, 0.0f));

		for (auto* component : this->mComponents)
		{
			component->OnUpdateWorldTransform();
		}
	}
}

void Actor::AddComponent(Component* component)
{
	auto myOrder = component->GetUpdateOrder();
	auto iter = this->mComponents.begin();
	for (; iter != this->mComponents.end(); ++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	this->mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(this->mComponents.begin(), this->mComponents.end(), component);
	if (iter != this->mComponents.end())
	{
		this->mComponents.erase(iter);
	}
}
