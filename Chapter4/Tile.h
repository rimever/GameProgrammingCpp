//
// Created on 2021/02/06.
//

#ifndef CHAPTER4_TILE_H
#define CHAPTER4_TILE_H


#include "Actor.h"
#include <vector>

class Tile : public Actor {
public:
    friend class Grid;

    enum TileState {
        EDefault,
        EPath,
        EStart,
        EBase
    };

    Tile(class Game *game);

    void SetTileState(TileState state);

    TileState GetTileState() const { return this->mTileState; }

    void ToggleSelect();

    const Tile *GetParent() const { return this->mParent; }

private:
    TileState mTileState;
    Tile *mParent;
    std::vector<Tile *> mAdjacent;
    float f;
    float g;
    float h;
    bool mInOpenSet;
    bool mInClosedSet;
    bool mBlocked;

    void UpdateTexture();

    class SpriteComponent *mSprite;

    bool mSelected;
};


#endif //CHAPTER4_TILE_H
