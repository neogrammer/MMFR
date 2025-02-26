#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <Animation/Animator.h>

class DynamicObject : public GameObject
{
public:
    sf::Vector2f velocity{};
    sf::Vector2f acceleration{};
  
    // We can store a shape for debugging or actual rendering
    sf::RectangleShape shape;
protected:
    Animator animator;
public:
    //sf::Vector2f tempPosition{};
    //sf::Vector2f tempVelocity{};
    //sf::Vector2f oldPosition{};
    //sf::Vector2f oldVelocity{};

    DynamicObject(std::string filename_, float x_ = 0.f, float y_ = 0.f);
    ~DynamicObject();

    // Example override for Update
    void Update(float dt_) override;

    // Example override for physics
    void FixedUpdate(float fps60_) override;

    // We can override a draw method if you want
    virtual void Render(sf::RenderWindow& wnd_) override;
    virtual BBox& getBBox() override;
    inline int getCurrentIndex() { return animator.getCurrIndex(); }
    sf::Vector2f currVelocity() { return velocity; }
    void setVelocity(sf::Vector2f vel) { velocity = vel; }

};