//
// Created on 2021/02/06.
//

#include "Game.h"
#include "SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Grid.h"
#include "Enemy.h"
#include "AIComponent.h"
#include "AIState.h"

Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mUpdatingActors(false) {

}

bool Game::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 4)", 100, 100, 1024, 768, 0);
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

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
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
    if (keyState[SDL_SCANCODE_B]) {
        mGrid->BuildTower();
    }

    int x, y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT) {
        this->mGrid->ProcessClick(x, y);
    }
    this->mUpdatingActors = true;
    for (auto actor:this->mActors) {
        actor->ProcessInput(keyState);
    }
    this->mUpdatingActors = false;
}

void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), this->mTicksCount + 16));
    float deltaTime = (SDL_GetTicks() - this->mTicksCount) / 1000.f;
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    this->mTicksCount = SDL_GetTicks();

    this->mUpdatingActors = true;
    for (auto actor:this->mActors) {
        actor->Update(deltaTime);
    }
    this->mUpdatingActors = false;
    for (auto pending:this->mPendingActors) {
        this->mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    std::vector<Actor *> deadActors;
    for (auto actor: this->mActors) {
        if (actor->GetState() == Actor::EDead) {
            deadActors.emplace_back(actor);
        }
    }
    for (auto actor:deadActors) {
        delete actor;
    }
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(this->mRenderer, 34, 139, 34, 255);
    SDL_RenderClear(this->mRenderer);
    for (auto sprite: this->mSprites) {
        sprite->Draw(this->mRenderer);
    }
    SDL_RenderPresent(this->mRenderer);
}

void Game::LoadData() {
    this->mGrid = new Grid(this);
}

void Game::UnloadData() {
    while (!this->mActors.empty()) {
        delete mActors.back();
    }
    for (auto i : this->mTextures) {
        SDL_DestroyTexture(i.second);
    }
    this->mTextures.clear();
}

SDL_Texture *Game::GetTexture(const std::string &fileName) {
    SDL_Texture *tex = nullptr;
    auto iter = this->mTextures.find(fileName);
    if (iter != this->mTextures.end()) {
        tex = iter->second;
    } else {
        SDL_Surface *surface = IMG_Load(fileName.c_str());
        if (!surface) {
            SDL_Log("Failed to load texture file  %s", fileName.c_str());
            return nullptr;
        }
        tex = SDL_CreateTextureFromSurface(this->mRenderer, surface);
        SDL_FreeSurface(surface);
        if (!tex) {
            SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
            return nullptr;
        }
        this->mTextures.emplace(fileName.c_str(), tex);
    }
    return tex;
}

void Game::Shutdown() {
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(this->mRenderer);
    SDL_DestroyWindow(this->mWindow);
    SDL_Quit();
}

void Game::AddActor(class Actor *actor) {
    if (this->mUpdatingActors) {
        this->mPendingActors.emplace_back(actor);
    } else {
        this->mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(class Actor *actor) {
    auto iter = std::find(this->mPendingActors.begin(), this->mPendingActors.end(), actor);
    if (iter != this->mPendingActors.end()) {
        std::iter_swap(iter, this->mPendingActors.end() - 1);
        this->mPendingActors.pop_back();
    }
    iter = std::find(this->mActors.begin(), this->mActors.end(), actor);
    if (iter != this->mActors.end()) {
        std::iter_swap(iter, this->mActors.end() - 1);
        this->mActors.pop_back();
    }
}

void Game::AddSprite(class SpriteComponent *sprite) {
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = this->mSprites.begin();
    for (; iter != this->mSprites.end(); ++iter) {
        if (myDrawOrder < (*iter)->GetDrawOrder()) {
            break;
        }
    }
    this->mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(class SpriteComponent *sprite) {
    auto iter = std::find(this->mSprites.begin(), this->mSprites.end(), sprite);
    this->mSprites.erase(iter);
}

Enemy *Game::GetNearestEnemy(const Vector2 &pos) {
    Enemy *best = nullptr;
    if (this->mEnemies.size() > 0) {
        best = this->mEnemies[0];
        float bestDistSq = (pos - this->mEnemies[0]->GetPosition()).LengthSq();
        for (size_t i = 1; i < this->mEnemies.size(); i++) {
            float newDistSq = (pos - this->mEnemies[i]->GetPosition()).LengthSq();
            if (newDistSq < bestDistSq) {
                bestDistSq = newDistSq;
                best = this->mEnemies[i];
            }
        }
    }
    return best;
}
