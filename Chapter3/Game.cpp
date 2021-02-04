//
// Created on 2021/02/04.
//

#include "Game.h"
#include "SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "Random.h"
#include "Asteroid.h"

Game::Game()
:mWindow(nullptr),mRenderer(nullptr),mIsRunning(true),mUpdatingActors(false){

}

bool Game::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s",SDL_GetError());
        return false;
    }
    this->mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter3)",100,100,1024,768,0);
    if (!this->mWindow) {
        SDL_Log("Failed to create window: %s",SDL_GetError());
        return false;
    }
    this->mRenderer = SDL_CreateRenderer(this->mWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (!this->mRenderer) {
        SDL_Log("Failed to create renderer: %s",SDL_GetError());
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("Unable to initialize SDL_image: %s",SDL_GetError());
        return false;
    }
    Random::Init();
    LoadData();
    this->mTicksCount = SDL_GetTicks();
    return true;
}

void Game::RunLoop() {
    while (this->mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
SDL_Event event;
while (SDL_PollEvent(&event)) {
    switch (event.type) {
        case SDL_QUIT:
            this->mIsRunning = false;
            break;
    }

}
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_ESCAPE]) {
        this->mIsRunning = false;
    }
    this->mUpdatingActors = true;
    for (auto actor:this->mActors) {
        actor->ProcessInput(keyState);
    }
    this->mUpdatingActors = false;
}

void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(),this->mTicksCount + 16))
        ;
    float deltaTime = (SDL_GetTicks()- this->mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    this->mTicksCount = SDL_GetTicks();

    this->mUpdatingActors = true;
    for (auto actor:this->mActors) {
        actor->Update(deltaTime);
    }
    this->mUpdatingActors = false;
    for (auto actor:this->mPendingActors) {
        this->mActors.emplace_back(actor);
    }
    mPendingActors.clear();
    std::vector<Actor*> deadActors;
    for (auto actor:this->mActors) {
        if (actor->GetState() == Actor::EDead) {
            deadActors.emplace_back(actor);
        }
    }

    for (auto actor:deadActors) {
        delete actor;
    }
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(this->mRenderer,220,220,220,255);
    SDL_RenderClear(this->mRenderer);

    for (auto sprite:this->mSprites) {
        sprite->Draw(this->mRenderer);
    }
    SDL_RenderPresent(this->mRenderer);
}

void Game::LoadData() {
    this->mShip = new Ship(this);
    this->mShip->SetPosition(Vector2(512.f,384.f));
    this->mShip->SetRotation(Math::PiOver2);

    const int numAsteroids = 20;
    for (int i = 0; i < numAsteroids; i++) {
        new Asteroid(this);
    }
}

void Game::UnloadData() {
    while (!this->mActors.empty()) {
        delete this->mActors.back();
    }
    for (auto i : this->mTextures) {
        SDL_DestroyTexture(i.second);
    }
    this->mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string &fileName) {
    SDL_Texture* tex = nullptr;
    auto iter = this->mTextures.find(fileName);
    if (iter!= this->mTextures.end()) {
        tex = iter->second;
    }else {
        SDL_Surface* surface = IMG_Load(fileName.c_str());
        if (!surface) {
            SDL_Log("Failed to load texture file %s" ,fileName.c_str());
            return nullptr;
        }
        tex = SDL_CreateTextureFromSurface(this->mRenderer,surface);
        SDL_FreeSurface(surface);
        if (!tex) {
            SDL_Log("Failed to convert surface to texture for %s",fileName.c_str());
            return nullptr;
        }
        this->mTextures.emplace(fileName.c_str(),tex);

    }
    return tex;
}

void Game::AddAsteroid(Asteroid* ast)
{
    mAsteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast)
{
    auto iter = std::find(mAsteroids.begin(),
                          mAsteroids.end(), ast);
    if (iter != mAsteroids.end())
    {
        mAsteroids.erase(iter);
    }
}

void Game::Shutdown()
{
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
    // If we're updating actors, need to add to pending
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor)
{
    // Is it in pending actors?
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    // Is it in actors?
    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::AddSprite(SpriteComponent* sprite)
{
    // Find the insertion point in the sorted vector
    // (The first element with a higher draw order than me)
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for ( ;
            iter != mSprites.end();
            ++iter)
    {
        if (myDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }

    // Inserts element before position of iterator
    mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
    // (We can't swap because it ruins ordering)
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}