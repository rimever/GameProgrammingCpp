//
//

#ifndef CHAPTER1_GAME_H
#define CHAPTER1_GAME_H

#include <SDL.h>

struct Vector2 {
    float x;
    float y;
};

class Game {

    void ProcessInput();

    void UpdateGame();

    void GenerateOutput();

    Vector2 mPaddlePos{};
    Vector2 mBallPos{};
    Vector2 mBallVel{};
    bool mIsRunning;
    int mPaddleDir;
    Uint32 mTicksCount;
    SDL_Renderer *mRenderer;
    SDL_Window *mWindow;
public:
    Game();

    bool Initialize();

    void RunLoop();

    void Shutdown();
};


#endif //CHAPTER1_GAME_H
