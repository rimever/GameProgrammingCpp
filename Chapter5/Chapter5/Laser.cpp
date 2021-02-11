#include "Laser.h"



#include "Asteroid.h"
#include "CircleComponent.h"
#include "Game.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"

Laser::Laser(Game* game): Actor(game), mDeathTimer(1.0f)
{
	auto* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	auto* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);

	this->mCircle = new CircleComponent(this);
	this->mCircle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime)
{
	this->mDeathTimer -= deltaTime;
	if (this->mDeathTimer < 0.0f)
	{
		SetState(EDead);
	}
	else
	{
		for (auto* asteroid : this->GetGame()->GetAsteroids())
		{
			if (Intersect(*this->mCircle, *(asteroid->GetCircle())))
			{
				this->SetState(EDead);
				asteroid->SetState(EDead);
				break;
			}
		}
	}
}
