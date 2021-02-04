//
// Created on 2021/02/04.
//

#ifndef CHAPTER2_BGSPRITECOMPONENT_H
#define CHAPTER2_BGSPRITECOMPONENT_H


#include <SDL_render.h>
#include "SpriteComponent.h"

class BGSpriteComponent : public SpriteComponent {
public:
    BGSpriteComponent(class Actor *owner, int drawOrder = 10);

    void Update(float deltaTime) override;

    void Draw(SDL_Renderer *renderer) override;

    void SetBGTextures(const std::vector<SDL_Texture *> &textures);

    void SetScreenSize(const Vector2 &size) { this->mScreenSize = size; }

    void SetScrollSpeed(float speed) { this->mScrollSpeed = speed; }

    float GetScrollSpeed() const { return this->mScrollSpeed; }

private:
    struct BGTexture {
        SDL_Texture *mTexture;
        Vector2 mOffset;
    };
    std::vector<BGTexture> mBGTextures;
    Vector2 mScreenSize;
    float mScrollSpeed;
};


#endif //CHAPTER2_BGSPRITECOMPONENT_H
