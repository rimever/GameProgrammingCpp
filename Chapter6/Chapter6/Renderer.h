#pragma once
#include <SDL_video.h>
#include <string>
#include <unordered_map>


#include "Math.h"

struct DirectionalLight
{
	Vector3 mDirection;
	Vector3 mDiffuseColor;
	Vector3 mSpecColor;
};

class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer() = default;

	bool Initialize(float screenWidth,float screenHeight);
	void Shutdown() const;
	void UnloadData();

	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddMeshComponent(class MeshComponent* mesh);
	void RemoveMeshComponent(class MeshComponent* mesh);

	class Texture* GetTexture(const std::string& fileName);
	class Mesh* GetMesh(const std::string& fileName);

	void SetViewMatrix(const Matrix4& view) { mView = view;}

void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient;}
	DirectionalLight& GetDirectionalLight() { return mDirLight;}

float GetScreenWidth() const { return mScreenWidth;}
float GetScreenHeight() const { return mScreenHeight;}
private:
	bool LoadShader();
	void CreateSpriteVerts();
	void SetLightUniforms(class Shader* shader) const;

	std::unordered_map<std::string, class Texture*> mTextures;
	std::unordered_map<std::string, class Mesh*>mMeshes;
	std::vector<class SpriteComponent*> mSprites;
	std::vector<class MeshComponent*> mMeshComps;
	class Game* mGame;
	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;
	class Shader* mMeshShader;
	Matrix4 mView;
	Matrix4 mProjection;
	float mScreenWidth;
	float mScreenHeight;
	Vector3 mAmbientLight;
	DirectionalLight mDirLight;

	SDL_Window* mWindow;
	SDL_GLContext mContext;
	

};

