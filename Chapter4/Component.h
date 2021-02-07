//
// Created on 2021/02/05.
//

#ifndef CHAPTER4_COMPONENT_H
#define CHAPTER4_COMPONENT_H
#include <cstdint>

class Component {
public:
    Component(class Actor* owner,int updateOrder=100);
    virtual ~Component();
    virtual void Update(float deltaTime);
    virtual void ProcessInput(const u_int8_t* keyState) {}
    int GetUpdateOrder() const { return this->mUpdateOrder;}

protected:
    class Actor* mOwner;
    int mUpdateOrder;
};


#endif //CHAPTER4_COMPONENT_H
