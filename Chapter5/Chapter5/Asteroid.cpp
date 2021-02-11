#include "Asteroid.h"


#include "CircleComponent.h"
#include "Game.h"
#include "MoveComponent.h"
#include "Random.h"
#include "SpriteComponent.h"

Asteroid::Asteroid(Game* game): Actor(game), mCircle(nullptr)
{
	auto randPos = Random::GetVector(Vector2(-512.0f, -384.0f), Vector2(512.0f, 384.0f));
	this->SetPosition(randPos);
	this->SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
	auto* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	auto* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	this->mCircle = new CircleComponent(this);
	this->mCircle->SetRadius(40.0f);

	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
