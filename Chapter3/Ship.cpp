//
// Created on 2021/02/04.
//

#include "Ship.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Laser.h"

Ship::Ship(class Game *game) : Actor(game), mLaserCooldown(0.0f) {
    SpriteComponent *sc = new SpriteComponent(this, 150);
    sc->SetTexture(game->GetTexture("Assets/Ship.png"));

    InputComponent *ic = new InputComponent(this);
    ic->SetForwardKey(SDL_SCANCODE_W);
    ic->SetBackKey(SDL_SCANCODE_S);
    ic->SetClockwiseKey(SDL_SCANCODE_A);
    ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
    ic->SetMaxForwardSpeed(100.0f);
    ic->SetMaxAngularSpeed(Math::TwoPi);
}

void Ship::UpdateActor(float deltaTime) {
    mLaserCooldown -= deltaTime;
}

void Ship::ActorInput(const uint8_t *keyState) {
    if (keyState[SDL_SCANCODE_SPACE] && this->mLaserCooldown <= 0.0f) {
        Laser *laser = new Laser(GetGame());
        laser->SetPosition(GetPosition());
        laser->SetRotation(GetRotation());
        this->mLaserCooldown = 0.5f;
    }
}