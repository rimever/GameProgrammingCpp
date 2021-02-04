//
// Created on 2021/02/04.
//

#include "Asteroid.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Game.h"

Asteroid::Asteroid(class Game *game)
        : Actor(game), mCircle(nullptr) {
    Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.f, 768.f));
    SetPosition(randPos);
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
    SpriteComponent *sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

    MoveComponent *mc = new MoveComponent(this);
    mc->SetForwardSpeed(150.0f);

    this->mCircle = new CircleComponent(this);
    this->mCircle->SetRadius(40.0f);
    game->AddAsteroid(this);
}

Asteroid::~Asteroid() {
    GetGame()->RemoveAsteroid(this);
}