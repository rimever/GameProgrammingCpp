#include "Game.h"

#include <GL/glew.h>

#include "Actor.h"
#include "Asteroid.h"
#include "Shader.h"
#include "Ship.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "VertexArray.h"


Game::Game()
	: mSpriteShader(nullptr), mWindow(nullptr), mIsRunning(true), mUpdatingActors(false)
{
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	this->mWindow = SDL_CreateWindow("Game Programming in C++(Chapter5)", 100, 100, 1024, 768, SDL_WINDOW_OPENGL);
	if (!this->mWindow)
	{
		SDL_Log("Failed to create window:%s", SDL_GetError());
		return false;
	}
	this->mContext = SDL_GL_CreateContext(this->mWindow);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}
	glGetError();
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders");
		return false;
	}
	CreateSpriteVerts();
	LoadData();
	this->mTicksCount = SDL_GetTicks();
	return true;
}

void Game::RunLoop()
{
	while (this->mIsRunning)
	{
		this->ProcessInput();
		this->UpdateGame();
		this->GenerateOutput();
	}
}

void Game::Shutdown()
{
	UnloadData();
	delete this->mSpriteVerts;
	this->mSpriteShader->Unload();
	delete mSpriteShader;
	SDL_GL_DeleteContext(this->mContext);
	SDL_DestroyWindow(this->mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (this->mUpdatingActors)
	{
		this->mPendingActors.emplace_back(actor);
	}
	else
	{
		this->mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(this->mPendingActors.begin(), this->mPendingActors.end(), actor);
	if (iter != this->mPendingActors.end())
	{
		std::iter_swap(iter, this->mPendingActors.end() - 1);
		this->mPendingActors.pop_back();
	}
	iter = std::find(this->mActors.begin(), this->mActors.end(), actor);
	if (iter != this->mActors.end())
	{
		std::iter_swap(iter, this->mActors.end() - 1);
		this->mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	auto myDrawOrder = sprite->GetDrawOrder();
	auto iter = this->mSprites.begin();
	for (; iter != this->mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	this->mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(this->mSprites.begin(), this->mSprites.end(), sprite);
	this->mSprites.erase(iter);
}

void Game::AddAsteroid(Asteroid* asteroid)
{
	this->mAsteroids.emplace_back(asteroid);
}

void Game::RemoveAsteroid(Asteroid* asteroid)
{
	auto iter = std::find(this->mAsteroids.begin(), this->mAsteroids.end(), asteroid);
	if (iter != this->mAsteroids.end())
	{
		this->mAsteroids.erase(iter);
	}
}

Texture* Game::GetTexture(const std::string& fileName)
{
	Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != this->mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(fileName))
		{
			this->mTextures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			this->mIsRunning = false;
			break;
		}
	}
	auto keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		this->mIsRunning = false;
	}
	this->mUpdatingActors = true;
	for (auto* actor : this->mActors)
	{
		actor->ProcessInput(keyState);
	}
	this->mUpdatingActors = false;
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), this->mTicksCount + 16))
	{
	}
	auto deltaTime = (SDL_GetTicks() - this->mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	this->mTicksCount = SDL_GetTicks();

	this->mUpdatingActors = true;
	for (auto* actor : this->mActors)
	{
		actor->Update(deltaTime);
	}
	this->mUpdatingActors = false;
	
	for (auto* pending : this->mPendingActors)
	{
		pending->ComputeWorldTransform();
		this->mActors.emplace_back(pending);
	}
	this->mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto* actor : this->mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto* actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->mSpriteShader->SetActive();
	this->mSpriteVerts->SetActive();
	for (auto* sprite : this->mSprites)
	{
		sprite->Draw(this->mSpriteShader);
	}
	SDL_GL_SwapWindow(this->mWindow);
}

bool Game::LoadShaders()
{
	this->mSpriteShader = new Shader();
	if (!this->mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}
	this->mSpriteShader->SetActive();
	auto viewProj = Matrix4::CreateSimpleViewProj(1024.f, 768.f);
	this->mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	return true;
}

void Game::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, // top left
		0.5f, 0.5f, 0.f, 1.f, 0.f, // top right
		0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
		-0.5f, -0.5f, 0.f, 0.f, 1.f // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void Game::LoadData()
{
	this->mShip = new Ship(this);
	this->mShip->SetRotation(Math::PiOver2);
	const auto numAsteroids = 20;
	for (auto i = 0; i < numAsteroids; i++)
	{
		new Asteroid(this);
	}
}

void Game::UnloadData()
{
	while (!this->mActors.empty())
	{
		delete this->mActors.back();
	}
	for (auto i : this->mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	this->mTextures.clear();
}
