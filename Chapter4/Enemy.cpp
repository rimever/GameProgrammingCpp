//
// Created on 2021/02/06.
//

#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "NavComponent.h"
#include "Grid.h"
#include "Tile.h"
#include "CircleComponent.h"
#include <algorithm>

Enemy::Enemy(class Game *game) : Actor(game) {
    game->GetEnemies().emplace_back(this);

    SpriteComponent *sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("Assets/Airplane.png"));
    SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());
    NavComponent *nc = new NavComponent(this);
    nc->SetForwardSpeed(150.f);
    nc->StartPath(GetGame()->GetGrid()->GetStartTile());
    this->mCircle = new CircleComponent(this);
    this->mCircle->SetRadius(25.f);
}

Enemy::~Enemy() {
    auto iter = std::find(GetGame()->GetEnemies().begin(), GetGame()->GetEnemies().end(), this);
    GetGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);
    Vector2 diff = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
    if (Math::NearZero(diff.Length(), 10.0f)) {
        SetState(EDead);
    }
}