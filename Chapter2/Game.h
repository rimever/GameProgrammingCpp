

#ifndef CHAPTER2_GAME_H
#define CHAPTER2_GAME_H


#include <unordered_map>
#include "Ship.h"
#include "SDL.h"
#include <string>
#include <vector>

class Game {
public:
    Game();

    void AddActor(class Actor *actor);

    void RemoveActor(class Actor *actor);

    bool Initialize();

    void RunLoop();

    void ShutDown();


    void AddSprite(class SpriteComponent *sprite);

    void RemoveSprite(class SpriteComponent *sprite);

    SDL_Texture *GetTexture(const std::string &fileName);

    void Shutdown();

private:
    void ProcessInput();

    void UpdateGame();

    void GenerateOutput();

    void LoadData();

    void UnloadData();

    std::unordered_map<std::string, SDL_Texture*> mTextures;

    std::vector<class Actor *> mActors;

    std::vector<class Actor *> mPendingActors;

    std::vector<class SpriteComponent *> mSprites;

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    Uint32 mTicksCount;


    bool mIsRunning;


    class Ship *mShip;

    bool mUpdatingActors;
};


#endif //CHAPTER2_GAME_H
