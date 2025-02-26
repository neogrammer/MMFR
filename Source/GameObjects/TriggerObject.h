#pragma once
#include "GameObject.h"

class TriggerObject : public GameObject
{
public:
	TriggerObject(std::string filename_, float x_ = 0.f, float y_ = 0.f);
    ~TriggerObject();
};