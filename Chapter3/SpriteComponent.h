//
// Created on 2021/02/04.
//

#ifndef CHAPTER3_SPRITECOMPONENT_H
#define CHAPTER3_SPRITECOMPONENT_H


#pragma
#include "Component.h"
#include "SDL.h"
class SpriteComponent:public Component {
public:
    SpriteComponent(class Actor* owner,int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    int GetDrawOrder() const { return this->mDrawOrder;}
    int GetTextureHeight() const { return this->mTexHeight;}
int GetTexWidth() const { return this->mTexWidth;}

protected:
    int mTexHeight;
    int mDrawOrder;
    int mTexWidth;
    SDL_Texture* mTexture;
};


#endif //CHAPTER3_SPRITECOMPONENT_H
