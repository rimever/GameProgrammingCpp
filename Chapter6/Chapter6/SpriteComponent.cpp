#include "SpriteComponent.h"

#include "Actor.h"
#include "Game.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder):
Component(owner),mTexture(nullptr),mDrawOrder(drawOrder),mTexWidth(0),mTexHeight(0)
{
	mOwner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	if (mTexture)
	{
		auto scaleMatrix = Matrix4::CreateScale(static_cast<float>(mTexWidth),static_cast<float>(mTexHeight),1.0f);
		auto world = scaleMatrix * mOwner->GetWorldTransform();
		shader->SetMatrixUniform("uWorldTransform",world);
		mTexture->SetActive();
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);
	}
}
void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}


