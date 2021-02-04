#include <SDL_render.h>
#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor *owner, int drawOrder)
        : SpriteComponent(owner, drawOrder), mCurrFrame(0.f), mAnimFPS(24.f) {

}

void AnimSpriteComponent::Update(float deltaTime) {
    SpriteComponent::Update(deltaTime);
    if (this->mAnimTextures.size() > 0) {
        this->mCurrFrame += this->mAnimFPS * deltaTime;
        while (this->mCurrFrame >= this->mAnimTextures.size()) {
            this->mCurrFrame -= this->mAnimTextures.size();
        }
        this->SetTexture(this->mAnimTextures[static_cast<int>(this->mCurrFrame)]);
    }
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture *> &textures) {
    this->mAnimTextures = textures;
    if (this->mAnimTextures.size() > 0) {
        this->mCurrFrame = 0.0f;
        this->SetTexture(this->mAnimTextures[0]);
    }
}