//
// Created on 2021/02/05.
//

#include "Bullet.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "Enemy.h"

Bullet::Bullet(class Game *game) : Actor(game) {
    SpriteComponent *sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("Assets/Projectile.png"));

    MoveComponent *mc = new MoveComponent(this);
    mc->SetForwardSpeed(400.0f);

    this->mCircle = new CircleComponent(this);
    this->mCircle->SetRadius(5.0f);
    this->mLiveTime = 1.0f;
}

void Bullet::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);
    for (Enemy *e : GetGame()->GetEnemies()) {
        if (Intersect(*mCircle, *(e->GetCircle()))) {
            e->SetState(EDead);
            SetState(EDead);
            break;
        }
    }
    this->mLiveTime -= deltaTime;
    if (this->mLiveTime <= 0.0f) {
        SetState(EDead);
    }
}