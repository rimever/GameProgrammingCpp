//
// Created on 2021/02/03.
//

#ifndef CHAPTER2_COMPONENT_H
#define CHAPTER2_COMPONENT_H


#include "Actor.h"

class Component {
public:
    Component(class Actor *owner, int updateOrder = 100);

    virtual ~Component();

    virtual void Update(float deltaTime);

    int GetUpdateOrder() const { return this->mUpdateOrder; }

protected:

    class Actor *mOwner;

    int mUpdateOrder;
};


#endif //CHAPTER2_COMPONENT_H
