//
// Created on 2021/02/04.
//

#ifndef CHAPTER3_COMPONENT_H
#define CHAPTER3_COMPONENT_H

#include <cstdint>
#include "Actor.h"

class Component {
public:
    Component(class Actor* owner,int updateOrder = 100);
    virtual ~Component();
    virtual void Update(float deltaTime);
    virtual void ProcessInput(const uint8_t* keyState) {}
    int GetUpdateOrder() const { return this->mUpdateOrder;}

protected:
    class Actor* mOwner;
    int mUpdateOrder;
};


#endif //CHAPTER3_COMPONENT_H
