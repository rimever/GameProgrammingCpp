#ifndef CHAPTER2_ANIMSPRITECOMPONENT_H
#define CHAPTER2_ANIMSPRITECOMPONENT_H


#include "SpriteComponent.h"

class AnimSpriteComponent : public SpriteComponent {
public:
    AnimSpriteComponent(class Actor *, int drawOrder = 100);

    void SetAnimTextures(const std::vector<SDL_Texture *> &textures);

    void Update(float deltaTime) override;

    float GetAnimFPS() const { return this->mAnimFPS; }

    void SetAnimFPS(float fps) { this->mAnimFPS = fps; }

private:
    std::vector<SDL_Texture *> mAnimTextures;
    float mCurrFrame;
    float mAnimFPS;
};


#endif //CHAPTER2_ANIMSPRITECOMPONENT_H
