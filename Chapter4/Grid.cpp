//
// Created on 2021/02/06.
//

#include "Grid.h"
#include "Tile.h"
#include "Tower.h"
#include "Enemy.h"
#include <algorithm>

Grid::Grid(class Game *game) : Actor(game), mSelectedTile(nullptr) {
    this->mTiles.resize(NumRows);
    for (size_t i = 0; i < NumRows; ++i) {
        mTiles[i].resize(NumCols);
    }
    for (size_t i = 0; i < NumRows; ++i) {
        for (size_t j = 0; j < NumCols; ++j) {
            this->mTiles[i][j] = new Tile(GetGame());
            this->mTiles[i][j]->SetPosition(Vector2(TileSize / 2.0f + j * TileSize, StartY + i * TileSize));
        }
    }
    GetStartTile()->SetTileState(Tile::EStart);
    GetEndTile()->SetTileState(Tile::EBase);
    for (size_t i = 0; i < NumRows; i++) {
        for (size_t j = 0; j < NumCols; ++j) {
            if (i > 0) {
                this->mTiles[i][j]->mAdjacent.push_back(this->mTiles[i - 1][j]);
            }
            if (i < NumRows - 1) {
                this->mTiles[i][j]->mAdjacent.push_back(this->mTiles[i + 1][j]);
            }
            if (i > 0) {
                this->mTiles[i][j]->mAdjacent.push_back(this->mTiles[i][j - 1]);
            }
            if (i < NumCols - 1) {
                this->mTiles[i][j]->mAdjacent.push_back(this->mTiles[i][j + 1]);
            }
        }
    }
    FindPath(GetEndTile(), GetStartTile());
    UpdatePathTiles(GetStartTile());
    this->mNextEnemy = this->EnemyTime;
}

void Grid::SelectTile(size_t row, size_t col) {
    Tile::TileState state = this->mTiles[row][col]->GetTileState();
    if (state != Tile::EStart && state != Tile::EBase) {
        if (this->mSelectedTile) {
            this->mSelectedTile->ToggleSelect();
        }
        this->mSelectedTile = this->mTiles[row][col];
        this->mSelectedTile->ToggleSelect();
    }
}

void Grid::ProcessClick(int x, int y) {
    y -= static_cast<int>(StartY - TileSize / 2);
    if (y >= 0) {
        x /= static_cast<int>(TileSize);
        y /= static_cast<int>(TileSize);
        if (x >= 0 && static_cast<int>(NumCols) && y >= 0 && y < static_cast<int>(NumRows)) {
            SelectTile(y, x);
        }
    }
}

bool Grid::FindPath(class Tile *start, class Tile *goal) {
    for (size_t i = 0; i < NumRows; i++) {
        for (size_t j = 0; j < NumCols; ++j) {
            this->mTiles[i][j]->g = 0.0f;
            this->mTiles[i][j]->mInOpenSet = false;
            this->mTiles[i][j]->mInClosedSet = false;

        }
    }
    std::vector<Tile *> openSet;
    Tile *current = start;
    current->mInClosedSet = true;
    do {
        for (Tile *neighbor : current->mAdjacent) {
            if (neighbor->mBlocked) {
                continue;
            }
            if (!neighbor->mInClosedSet) {
                if (!neighbor->mInOpenSet) {
                    neighbor->mParent = current;
                    neighbor->h = (neighbor->GetPosition() - goal->GetPosition()).Length();
                    neighbor->g = current->g + TileSize;
                    neighbor->f = neighbor->g + neighbor->h;
                    openSet.emplace_back(neighbor);
                    neighbor->mInOpenSet = true;
                } else {
                    float newG = current->g + TileSize;
                    if (newG < neighbor->g) {
                        neighbor->mParent = current;
                        neighbor->g = newG;
                        neighbor->f = neighbor->g + neighbor->h;
                    }
                }
            }
        }
        if (openSet.empty()) {
            break;
        }
        auto iter = std::min_element(openSet.begin(), openSet.end(), [](Tile *a, Tile *b) {
            return a->f < b->f;
        });
        current = *iter;
        openSet.erase(iter);
        current->mInOpenSet = false;
        current->mInClosedSet = true;
    } while (current != goal);
    return (current == goal) ? true : false;
}

void Grid::UpdatePathTiles(class Tile *start) {
    for (size_t i = 0; i < NumRows; i++) {
        for (size_t j = 0; j < NumCols; ++j) {
            if (!(i == 3 && j == 0) && !(i == 3 && j == 15)) {
                this->mTiles[i][j]->SetTileState(Tile::EDefault);
            }

        }
    }
    Tile *t = start->mParent;
    while (t != GetEndTile()) {
        t->SetTileState(Tile::EPath);
        t = t->mParent;
    }
}

void Grid::BuildTower() {
    if (this->mSelectedTile && !this->mSelectedTile->mBlocked) {
        this->mSelectedTile->mBlocked = true;
        if (this->FindPath(this->GetEndTile(), this->GetStartTile())) {
            Tower *tower = new Tower(GetGame());
            tower->SetPosition(this->mSelectedTile->GetPosition());
        } else {
            this->mSelectedTile->mBlocked = false;
            this->FindPath(this->GetEndTile(), this->GetStartTile());
        }
        this->UpdatePathTiles(GetStartTile());
    }
}

Tile *Grid::GetStartTile() {
    return this->mTiles[3][0];
}

Tile *Grid::GetEndTile() {
    return this->mTiles[3][15];
}

void Grid::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);
    this->mNextEnemy -= deltaTime;
    if (this->mNextEnemy <= 0.0f) {
        new Enemy(GetGame());
        this->mNextEnemy += EnemyTime;
    }
}