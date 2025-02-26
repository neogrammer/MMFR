#include "StaticObject.h"

StaticObject::StaticObject(std::string filename_, float x_, float y_)
    : GameObject{ filename_, x_, y_ }
    , shape{}
{
    auto width = getBBox().width;
    auto height = getBBox().height;

    shape.setSize({ width, height });
    shape.setFillColor(sf::Color::Yellow); // or whatever
    shape.setPosition(x_, y_);
}

StaticObject::~StaticObject()
{
}

void StaticObject::Update(float dt_)
{
    // If truly static, maybe nothing here
    // But if we do animation, we might move something around
}

void StaticObject::Render(sf::RenderWindow& wnd_)
{
    wnd_.draw(shape);
}