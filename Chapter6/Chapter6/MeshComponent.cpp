#include "MeshComponent.h"

#include "Actor.h"
#include "Game.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Renderer.h"

MeshComponent::MeshComponent(Actor* owner)
	:Component(owner)
,mMesh(nullptr)
,mTextureIndex(0)
{
	mOwner->GetGame()->GetRenderer()->AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{mOwner->GetGame()->GetRenderer()->RemoveMeshComponent(this);
}

void MeshComponent::Draw(Shader* shader)
{
	if (mMesh)
	{
		shader->SetMatrixUniform("uWorldTransform",mOwner->GetWorldTransform());
		shader->SetFloatUniform("uSpecPower",mMesh->GetSpecPower());
		auto *t = mMesh->GetTexture(mTextureIndex);
		if (t)
		{
			t->SetActive();
		}
		auto *vertexArray = mMesh->GetVertexArray();
		vertexArray->SetActive();

		glDrawElements(GL_TRIANGLES,vertexArray->GetNumIndices(),GL_UNSIGNED_INT,nullptr);
	}
}



