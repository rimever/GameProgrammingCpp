#pragma once
#include "Component.h"

class SpriteComponent : Component
{
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(class Shader* shader);
	virtual void SetTexture(class Texture* texture);

	int GetDrawOrder() const { return this->mDrawOrder; }
	int GetTexHeight() const { return this->mTexHeight; }
	int GetTexWidth() const { return this->mTexWidth; }
protected:
	class Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};
