//
// Created on 2021/02/06.
//

#include "Tower.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Enemy.h"
#include "Bullet.h"

Tower::Tower(class Game *game):Actor(game) {
    SpriteComponent* sc = new SpriteComponent(this,200);
    sc->SetTexture(game->GetTexture("Assets/Tower.png"));

    this->mMove = new MoveComponent(this);
    this->mNextAttack = AttackTime;
}

void Tower::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);
    this->mNextAttack -= deltaTime;
    if (this->mNextAttack <= 0.0f) {
        Enemy* e = GetGame()->GetNearestEnemy(GetPosition());
        if (e!= nullptr) {
            Vector2 dir = e->GetPosition() - GetPosition();
            float dist = dir.Length();
            if (dist < AttackRange) {
                SetRotation(Math::Atan2(-dir.y,dir.x));
                Bullet* bullet = new Bullet(GetGame());
                bullet->SetPosition(GetPosition());
                bullet->SetRotation(GetRotation());
            }
        }
        this->mNextAttack += AttackTime;
    }
}