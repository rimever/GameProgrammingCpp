#include "Actor.h"

#include "Component.h"
#include "Game.h"

Actor::Actor(Game* game)
	:mState(EActive)
,mPosition(Vector3::Zero)
,mRotation(Quaternion::Identity)
,mScale(1.0f)
,mGame(game)
,mRecomputeWorldTransform(true)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive)
	{
		ComputeWorldTransform();
		
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);

		ComputeWorldTransform();
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto* component : mComponents)
	{
		component->Update(deltaTime);
	}
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		for (auto* component:mComponents)
		{
			component->ProcessInput(keyState);
		}
		ActorInput(keyState);
	}
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);

		for (auto component: mComponents)
		{
			component->OnUpdateWorldTransform();
		}
	}
}

void Actor::AddComponent(Component* component)
{
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mComponents.insert(iter,component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(),mComponents.end(),component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}










