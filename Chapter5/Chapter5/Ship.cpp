#include "Ship.h"


#include "Game.h"
#include "SDL.h"

#include "InputComponent.h"
#include "Laser.h"
#include "SpriteComponent.h"

Ship::Ship(Game* game): Actor(game), mLaserCoolDown(0.0f)
{
	auto sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	auto ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCoolDown -= deltaTime;
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && this->mLaserCoolDown <= 0.0f)
	{
		auto* laser = new Laser(GetGame());
		laser->SetPosition(this->GetPosition());
		laser->SetRotation(this->GetRotation());
		this->mLaserCoolDown = 0.5f;
	}
}
