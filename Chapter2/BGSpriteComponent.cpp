//
// Created on 2021/02/04.
//

#include "BGSpriteComponent.h"

BGSpriteComponent::BGSpriteComponent(class Actor *owner, int drawOrder)
        : SpriteComponent(owner, drawOrder), mScrollSpeed(0.0f) {

}

void BGSpriteComponent::Update(float deltaTime) {
    SpriteComponent::Update(deltaTime);
    for (auto &bg :this->mBGTextures) {
        bg.mOffset.x += this->mScrollSpeed * deltaTime;
        if (bg.mOffset.x < this->mScreenSize.x) {
            bg.mOffset.x = (this->mBGTextures.size() - 1) * this->mScreenSize.x - 1;
        }
    }
}

void BGSpriteComponent::Draw(SDL_Renderer *renderer) {
    for (auto &bg:this->mBGTextures) {
        SDL_Rect r;
        r.w = static_cast<int>(this->mScreenSize.x);
        r.h = static_cast<int>(this->mScreenSize.y);
        r.x = static_cast<int>(this->mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
        r.y = static_cast<int>(this->mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);
        SDL_RenderCopy(renderer, bg.mTexture, nullptr, &r);
    }
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture *> &textures) {
    int count = 0;
    for (auto tex:textures) {
        BGTexture temp;
        temp.mTexture = tex;
        temp.mOffset.x = count * this->mScreenSize.x;
        temp.mOffset.y = 0;
        this->mBGTextures.emplace_back(temp);
        count++;
    }
}