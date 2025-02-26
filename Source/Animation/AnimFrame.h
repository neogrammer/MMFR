#pragma once

#include <SFML/Graphics.hpp>    
#include <Resources/Cfg.h>

struct AnimFrame
{
    // Sub-rectangle of the texture (e.g. which portion of the texture to draw)
    sf::IntRect textureRect;

    // Where to place the sprite relative to the object's (posx, posy).
    // For example, if the sprite is centered or offset.
    //sf::Vector2f drawOffset;

    // Possibly store a pointer or reference to the texture
    // (but you might also store just a texture ID and look it up).
    Cfg::Textures textureID;

};