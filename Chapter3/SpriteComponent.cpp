//
// Created on 2021/02/04.
//

#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(class Actor *owner, int drawOrder) : Component(owner), mTexture(nullptr),
                                                                      mDrawOrder(drawOrder), mTexWidth(0),
                                                                      mTexHeight(0) {
    this->mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    this->mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer *renderer) {
    if (this->mTexture) {
        SDL_Rect r;
        r.w = static_cast<int>(this->mTexWidth * this->mOwner->GetScale());
        r.h = static_cast<int>(this->mTexHeight * this->mOwner->GetScale());
        r.x = static_cast<int>(this->mOwner->GetPosition().x - r.w / 2);
        r.y = static_cast<int>(this->mOwner->GetPosition().y - r.h / 2);

        SDL_RenderCopyEx(renderer,
                         this->mTexture,
                         nullptr, &r, -Math::ToDegrees(this->mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
    }
}

void SpriteComponent::SetTexture(SDL_Texture *texture) {
    this->mTexture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &this->mTexWidth, &this->mTexHeight);
}