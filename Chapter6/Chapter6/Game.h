#pragma once
#include <SDL.h>
#include <vector>
class Renderer;

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	class Renderer* GetRenderer() const { return mRenderer;}
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput() const;
	void LoadData();
	void UnloadData();

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	
	            class Renderer* mRenderer;
	Uint32 mTicksCount{};
	bool mIsRunning;
	bool mUpdatingActors;
	class CameraActor* mCameraActor{};
};

