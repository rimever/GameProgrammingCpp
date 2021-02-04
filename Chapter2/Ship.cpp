#include <SDL_render.h>
#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Ship::Ship(Game *game)
        : Actor(game), mRightSpeed(0.f), mDownSpeed(0.f) {
    AnimSpriteComponent *asc = new AnimSpriteComponent(this);
    std::vector<SDL_Texture *> anims = {
            game->GetTexture("Assets/Ship01.png"),
            game->GetTexture("Assets/Ship02.png"),
            game->GetTexture("Assets/Ship03.png"),
            game->GetTexture("Assets/Ship04.png"),
    };
    asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);
    Vector2 pos = this->GetPosition();
    pos.x += this->mRightSpeed * deltaTime;
    pos.y += this->mDownSpeed * deltaTime;
    if (pos.x < 25.f) {
        pos.x = 25.f;
    } else if (pos.x > 500.f) {
        pos.x = 500.f;
    }
    if (pos.y < 25.f) {
        pos.y = 25.f;
    } else if (pos.y > 743.f) {
        pos.y = 743.f;
    }
    this->SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t *state) {
    this->mRightSpeed = 0.0f;
    this->mDownSpeed = 0.0f;
    if (state[SDL_SCANCODE_D]) {
        this->mRightSpeed += 250.f;

    }
    if (state[SDL_SCANCODE_A]) {
        this->mRightSpeed -= 250.f;
    }
    if (state[SDL_SCANCODE_S]) {
        this->mDownSpeed += 300.f;
    }
    if (state[SDL_SCANCODE_W]) {
        this->mDownSpeed -= 300.f;
    }
}
