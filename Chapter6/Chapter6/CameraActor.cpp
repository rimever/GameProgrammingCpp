#include "CameraActor.h"

#include <SDL_scancode.h>
#include "Game.h"
#include "MoveComponent.h"
#include "Renderer.h"

CameraActor::CameraActor(Game* game):Actor(game)
{
	mMoveComponent = new MoveComponent(this);
}

void CameraActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	auto cameraPos = GetPosition();
	auto target = GetPosition() + GetForward() * 100.0f;
	auto up = Vector3::UnitZ;

	auto view = Matrix4::CreateLookAt(cameraPos, target,up);
	GetGame()->GetRenderer()->SetViewMatrix(view);
}

void CameraActor::ActorInput(const uint8_t* keyState)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	if (keyState[SDL_SCANCODE_W])
	{
		forwardSpeed += 300.0f;
	}
	if (keyState[SDL_SCANCODE_S])
	{
		forwardSpeed -= 300.0f;
	}
	if (keyState[SDL_SCANCODE_A])
	{
		angularSpeed -= Math::TwoPi;
	}
	if (keyState[SDL_SCANCODE_D])
	{
		angularSpeed += Math::TwoPi;
	}
	mMoveComponent->SetForwardSpeed(forwardSpeed);
	mMoveComponent->SetAngularSpeed(angularSpeed);
}


