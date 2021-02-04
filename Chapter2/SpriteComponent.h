#ifndef CHAPTER2_SPRITECOMPONENT_H
#define CHAPTER2_SPRITECOMPONENT_H

#pragma once

#include <SDL_render.h>
#include "Component.h"


class SpriteComponent : public Component {

public:
    SpriteComponent(Actor *owner, int drawOrder = 100);

    ~SpriteComponent();

    virtual void Draw(SDL_Renderer *renderer);


    virtual void SetTexture(SDL_Texture *texture);

    int GetDrawOrder() const { return this->mDrawOrder; }

    int GetTexHeight() const { return this->mTexHeight; }

    int GetTextWidth() const { return this->mTexWidth; }

protected:
    SDL_Texture *mTexture;

    int mTexWidth;
    int mTexHeight;
    int mDrawOrder;
};


#endif //CHAPTER2_SPRITECOMPONENT_H
