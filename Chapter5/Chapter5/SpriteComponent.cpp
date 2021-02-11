#include "SpriteComponent.h"

#include <glew.h>


#include "Actor.h"
#include "Game.h"
#include "Shader.h"
#include "Texture.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	: Component(owner), mTexture(nullptr), mDrawOrder(drawOrder)
	  , mTexWidth(0), mTexHeight(0)
{
	this->mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	this->mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	if (mTexture)
	{
		const auto scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(this->mTexWidth),
			static_cast<float>(this->mTexHeight),
			1.0f);
		const auto world = scaleMatrix * this->mOwner->GetWorldTransform();
		shader->SetMatrixUniform("uWorldTransform", world);
		this->mTexture->SetActive();
		glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT, nullptr);
	}
}

void SpriteComponent::SetTexture(Texture* texture)
{
	this->mTexture = texture;
	this->mTexWidth = texture->GetWidth();
	this->mTexHeight = texture->GetHeight();
}
