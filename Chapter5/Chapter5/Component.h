#pragma once
#include <cstdint>

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float delta_time);
	virtual void ProcessInput(const uint8_t* key_state){}
	virtual void OnUpdateWorldTransform(){}
	int GetUpdateOrder() const { return this->mUpdateOrder; }
protected:
	class Actor* mOwner;
	int mUpdateOrder;
};
