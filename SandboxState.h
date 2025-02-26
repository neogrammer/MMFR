#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Physics/Physics.h"      // Your physics code
#include <Tilemap/Tile.h>
#include <GameObjects/Player/Player.h>
#include <Tilemap/Tilemap.h>
#include <Hodgepodge/Background.h>
class SandboxState
{
public:
    SandboxState(sf::RenderWindow& wnd_);
    ~SandboxState() = default;

    void ProcessInputStates();
    void Update(float dt_, sf::RenderWindow& wnd_);
    void UpdateFixed(float dt_);
    void Render(sf::RenderWindow& window);
    sf::View& gameViewRef();
private:
    Tilemap tilemap;
    Player player;
    Background bground;
    sf::View gameView;
    sf::FloatRect getViewBounds(const sf::View& view);
    //std::vector<Tile> groundTiles;

};