#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>
class StaticObject : public GameObject
{
protected:
    sf::RectangleShape shape; // if you want a shape for static objects, too
   
    

public:
    StaticObject(std::string filename_, float x_ = 0.f, float y_ = 0.f);
    ~StaticObject();

    // override the update if you need it
    virtual void Update(float dt_) override;

    virtual void Render(sf::RenderWindow& wnd_) override;
};