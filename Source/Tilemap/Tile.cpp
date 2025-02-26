#include "Tile.h"

Tile::Tile(float x_, float y_, float w_, float h_)
	: StaticObject{"ADDAFILEHERE", x_, y_}
	, x_{x_}
	, y_{y_}
	, w_{w_}
	, h_{h_}
	, tx_{0}
	, ty_{0}
	, tw_{ 0 }
	, th_{ 0 }
	, currFrame_{ 0 }
	, type_{Cfg::Textures::Invalid}
	, solid{false}
{

}
Tile::Tile(bool solid_, Cfg::Textures type, float x_, float y_, float w_, float h_ ,
	int tx_, int ty_, int tw_, int th_ )
	: StaticObject{ "ADDAFILEHERE", x_, y_ }
	, x_{ x_ }
	, y_{ y_ }
	, w_{ w_ }
	, h_{ h_ }
	, tx_{ tx_ }
	, ty_{ ty_ }
	, tw_{ tw_ }
	, th_{ th_ }
	, currFrame_{ 0 }
	, type_{ type }
	, solid{ solid_ }
{

}

Tile::Tile(sf::FloatRect worldRect_, sf::IntRect texRect_, bool solid_, Cfg::Textures type)
	: StaticObject{ "ADDAFILEHERE", x_, y_ }
	, x_{ worldRect_.getPosition().x }
	, y_{ worldRect_.getPosition().y }
	, w_{worldRect_.getSize().x }
	, h_{ worldRect_.getSize().y }
	, tx_{ texRect_.getPosition().x }
	, ty_{ texRect_.getPosition().y }
	, tw_{ texRect_.getSize().x }
	, th_{ texRect_.getSize().y }
	, currFrame_{ 0 }
	, type_{ type }
	, solid{ solid_ }
{

}

Tile::Tile(sf::IntRect texRect_, bool solid_, Cfg::Textures type)
	: StaticObject{ "ADDAFILEHERE", x_, y_ }
	, x_{ (float)texRect_.getPosition().x }
	, y_{ (float)texRect_.getPosition().y   }
	, w_ {(float)texRect_.getSize().x  }
	, h_{ (float)texRect_.getSize().y }
	, tx_{ texRect_.getPosition().x }
	, ty_{ texRect_.getPosition().y }
	, tw_{ texRect_.getSize().x }
	, th_{ texRect_.getSize().y}
	, currFrame_{ 0 }
	, type_{type }
	, solid{ solid_ }
{

}


Tile::~Tile()
{

}

void Tile::Update(float dt_)
{
}

void Tile::Render(sf::RenderWindow& wnd_)
{
	StaticObject::Render(wnd_);
}

void Tile::SetSolid(bool solid_)
{
	solid = solid_;
}

sf::FloatRect Tile::worldRect()
{
	return sf::FloatRect(x_, y_, w_, h_);
}

sf::IntRect Tile::texRect()
{
	return sf::IntRect(tx_,ty_,tw_,th_);
}

std::unique_ptr<sf::Sprite> Tile::getSprite()
{
	std::unique_ptr<sf::Sprite> tmp = std::make_unique<sf::Sprite>();
	tmp->setTexture(Cfg::textures.get((int)this->type_));
	tmp->setTextureRect(texRect());
	tmp->setPosition({ x_, y_ });
	return std::move(tmp);
}
