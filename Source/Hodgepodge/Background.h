#ifndef BACKGROUND_H__
#define BACKGROUND_H__
#include <SFML/Graphics.hpp>
#include <Resources/Cfg.h>
class Background
{ 
	std::vector<std::vector<sf::Vector2f>> positions;
	std::vector<sf::Vector2f> sizes;
	std::vector<Cfg::Textures> texID;
	int currentLevel = 0;
	bool isBGCopyBehind{ true };
	
public:
	void setParams(sf::Vector2f pos_, sf::Vector2f size_, Cfg::Textures texID_, int layer_, int level_);
	int currLevel() { return currentLevel;  }
	void setLevel(int lvlNum);
	void update(float dt_);
	void render(sf::RenderWindow& wnd_, sf::FloatRect viewBounds);

};

#endif