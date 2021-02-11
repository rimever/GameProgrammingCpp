#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "Math.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddAsteroid(class Asteroid* asteroid);
	void RemoveAsteroid(class Asteroid* asteroid);
	std::vector<class Asteroid*>& GetAsteroids() { return this->mAsteroids; }
	class Texture* GetTexture(const std::string& fileName);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool LoadShaders();
	void CreateSpriteVerts();
	void LoadData();
	void UnloadData();

	std::unordered_map<std::string, class Texture*> mTextures;
	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	std::vector<class SpriteComponent*> mSprites;
	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;
	SDL_Window* mWindow;
	SDL_GLContext mContext;
	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;

	class Ship* mShip;
	std::vector<Asteroid*> mAsteroids;
};
