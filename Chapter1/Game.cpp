//
//

#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
        :mWindow(nullptr)
        ,mRenderer(nullptr)
        ,mTicksCount(0)
        ,mIsRunning(true)
        ,mPaddleDir(0)
{

}

bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    this->mWindow = SDL_CreateWindow(
            "Game Programming in C++ (Chapter1)",
            100,
            100,
            1024,
            768,
            0
    );
    if (!this->mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    this->mRenderer = SDL_CreateRenderer(
            this->mWindow,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!this->mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
    this->mPaddlePos.x = 10.f;
    this->mPaddlePos.y = 768.f / 2.f;
    this->mBallPos.x = 1024.f / 2.f;
    this->mBallPos.y = 768.f / 2.f;
    this->mBallVel.x = -200.f;
    this->mBallVel.y = 235.f;
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
    this->mPaddleDir = 0;
    if (state[SDL_SCANCODE_W]) {
        this->mPaddleDir -= 1;
    }
    if (state[SDL_SCANCODE_S]) {
        this->mPaddleDir += 1;
    }
}

void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), this->mTicksCount + 16));
    float deltaTime = (SDL_GetTicks() - this->mTicksCount) / 1000.f;

    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    this->mTicksCount = SDL_GetTicks();
    if (this->mPaddleDir != 0) {
        this->mPaddlePos.y += this->mPaddleDir * 300.f * deltaTime;
        if (this->mPaddlePos.y < (paddleH / 2.f + thickness)) {
            this->mPaddlePos.y = paddleH / 2.f + thickness;
        } else if (this->mPaddlePos.y > (768.f - paddleH / 2.f - thickness)) {
            this->mPaddlePos.y = 768.f - paddleH / 2.f - thickness;
        }
    }
    this->mBallPos.x += mBallVel.x * deltaTime;
    this->mBallPos.y += mBallVel.y * deltaTime;

    float diff = this->mPaddlePos.y - this->mBallPos.y;
    diff = (diff > 0.f) ? diff : -diff;
    if (diff <= paddleH / 2.f
        && this->mBallPos.x <= 25.f && this->mBallPos.x >= 20.f
        && this->mBallVel.x < 0.f) {
        mBallVel.x *= -1.f;
    } else if (this->mBallPos.x >= (1024.f - thickness) && this->mBallVel.x > 0.f) {
        this->mBallVel.x *= -1.f;
    }

    if (this->mBallPos.y <= thickness && mBallVel.y < 0.f) {
        this->mBallVel.y *= -1;
    } else if (this->mBallPos.y >= (768 - thickness)
               && this->mBallVel.y > 0.f) {
        this->mBallVel.y *= -1;
    }
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(
            this->mRenderer,
            0,
            0,
            255,
            255
    );
    SDL_RenderClear(this->mRenderer);
    SDL_SetRenderDrawColor(this->mRenderer, 255, 255, 255, 255);
    SDL_Rect wall{
            0, 0, 1024, thickness
    };
    wall.y = 768 - thickness;
    SDL_RenderFillRect(this->mRenderer, &wall);
    wall.x = 1024 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 1024;
    SDL_RenderFillRect(this->mRenderer, &wall);

    SDL_Rect paddle{
            static_cast<int>(this->mPaddlePos.x),
            static_cast<int>(this->mPaddlePos.y - paddleH / 2),
            thickness,
            static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(this->mRenderer, &paddle);
    SDL_Rect ball{
            static_cast<int>(this->mBallPos.x - thickness / 2),
            static_cast<int>(this->mBallPos.y - thickness / 2),
            thickness,
            thickness
    };
    SDL_RenderFillRect(this->mRenderer, &ball);
    SDL_RenderPresent(this->mRenderer);
}

void Game::Shutdown() {
    SDL_DestroyRenderer(this->mRenderer);
    SDL_DestroyWindow(this->mWindow);
    SDL_Quit();
}

