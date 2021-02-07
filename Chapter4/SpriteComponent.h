//
// Created on 2021/02/05.
//

#ifndef CHAPTER4_SPRITECOMPONENT_H
#define CHAPTER4_SPRITECOMPONENT_H

#include "Component.h"
#include "SDL.h"
class SpriteComponent:public Component {
public:
    SpriteComponent(class Actor* owner,int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    int GetDrawOrder() const { return this->mDrawOrder;}
    int GetTexHeight() const {return this->mTexHeight;}
    int GetTextWidth() const { return this->mTexWidth;}
protected:
    int mDrawOrder;
    int mTexHeight;
    int mTexWidth;
    SDL_Texture* mTexture;
};


#endif //CHAPTER4_SPRITECOMPONENT_H
