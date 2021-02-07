//
// Created on 2021/02/06.
//

#include <string>
#include "Tile.h"
#include "SpriteComponent.h"
#include "Game.h"


Tile::Tile(class Game* game)
        :Actor(game), mParent(nullptr), f(0.0f), g(0.0f), h(0.0f), mBlocked(false), mSprite(nullptr),
          mTileState(EDefault), mSelected(false) {
    this->mSprite = new SpriteComponent(this);
    this->UpdateTexture();
}

void Tile::SetTileState(TileState state) {
    this->mTileState = state;
}

void Tile::ToggleSelect() {
    this->mSelected = !this->mSelected;
    this->UpdateTexture();
}

void Tile::UpdateTexture() {
    std::string text;
    switch (this->mTileState) {
        case EStart:
            text = "Assets/TileTan.png";
            break;
        case EBase:
            text = "Assets/TileGreen.png";
            break;
        case EPath:
            if (this->mSelected) {
                text = "Assets/TileGreySelected.png";
            } else {
                text = "Assets/TileGrey.png";
            }
            break;
        case EDefault:
        default:
            if (this->mSelected) {
                text = "Assets/TileBrownSelected.png";
            } else {
                text = "Assets/TileBrown.png";
            }

    }
    this->mSprite->SetTexture(this->GetGame()->GetTexture(text));
}