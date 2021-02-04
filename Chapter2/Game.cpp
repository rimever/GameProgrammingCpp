#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "BGSpriteComponent.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

Game::Game()
        : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mUpdatingActors(false) {

}

bool Game::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    this->mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 2)", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!this->mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    this->mRenderer = SDL_CreateRenderer(this->mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }
    this->LoadData();
    this->mTicksCount = SDL_GetTicks();
    return true;
}

void Game::RunLoop() {
    while (this->mIsRunning) {
        this->ProcessInput();
        this->UpdateGame();
        this->GenerateOutput();
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
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        this->mIsRunning = false;
    }
    this->mShip->ProcessKeyboard(state);
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

    for (auto pending : this->mPendingActors) {
        this->mActors.emplace_back(pending);
    }
    this->mPendingActors.clear();

    std::vector<Actor *> deadActors;
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
    SDL_SetRenderDrawColor(this->mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(this->mRenderer);
    for (auto sprite:this->mSprites) {
        sprite->Draw(this->mRenderer);
    }
    SDL_RenderPresent(this->mRenderer);
}

void Game::LoadData() {
    this->mShip = new Ship(this);
    this->mShip->SetPosition(Vector2(100.f, 384.f));
    this->mShip->SetScale(1.5f);
    Actor *temp = new Actor(this);
    temp->SetPosition(Vector2(512.f, 384.f));
    BGSpriteComponent *bg = new BGSpriteComponent(temp);
    bg->SetScreenSize(Vector2(1024.f, 768.f));
    std::vector<SDL_Texture *> bgtexs = {
            GetTexture("Assets/Farback01.png"),
            GetTexture("Assets/Farback02.png")
    };
    bg->SetBGTextures(bgtexs);
    bg->SetScrollSpeed(-100.f);

    bg = new BGSpriteComponent(temp, 50);
    bg->SetScreenSize(Vector2(1024.f, 768.f));
    bgtexs = {
            GetTexture("Assets/Stars.png"),
            GetTexture("Assets/Starts.png")
    };
    bg->SetBGTextures(bgtexs);
    bg->SetScrollSpeed(-200.f);
}

void Game::UnloadData() {
    while (!this->mActors.empty()) {
        delete this->mActors.back();
    }
    for (auto i :this->mTextures) {
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
            SDL_Log("Failed to load texture file %s", fileName.c_str());
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

