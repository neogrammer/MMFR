#pragma once
#include <string>
#include <sstream>
#include <memory>
#include <iostream>
#include <vector>
#include "Tile.h"
#include <Resources/Cfg.h>
#include <SFML/Graphics.hpp>

class Tilemap
{
	std::vector<Tile> tileset;
	std::vector<Tile> tiles;
	Cfg::Textures texID;
	int tw, th, mapW, mapH;

public:
	Tilemap() = delete;
	Tilemap(std::string filename, Cfg::Textures texID_);
	~Tilemap();

	std::vector<Tile>& getTiles();
	std::vector<Tile>& getTileset();
	Tile copyTilesetTile(int index);
	Tile& getTilemapTile(int index);
	int pitch() { return mapW; }

	void Render(sf::RenderWindow& wnd_);

};