//
// Created on 2021/02/04.
//

#ifndef CHAPTER3_CIRCLECOMPONENT_H
#define CHAPTER3_CIRCLECOMPONENT_H


#include "Component.h"
#include "Math.h"

class CircleComponent : public Component{
public:
    CircleComponent(class Actor* owner);

    void SetRadius(float  radius) { this->mRadius = radius;}
float GetRadius() const;
    const Vector2& GetCenter() const;
private:
    float mRadius;
};

bool Intersect(const CircleComponent& a,const CircleComponent& b);


#endif //CHAPTER3_CIRCLECOMPONENT_H
