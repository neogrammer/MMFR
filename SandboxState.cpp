#include "SandboxState.h"
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <algorithm>
SandboxState::SandboxState(sf::RenderWindow& wnd_)
// Suppose we have some “player.png” for now
    : player{}
    , tilemap("Assets/Data/Tilesets/Tileset1.txt", Cfg::Textures::Tileset1)
{
    // Force the bounding box to be 130×160 for this test
    player.getBBox().width = 48.f;
    player.getBBox().height = 60.f;

    // Create a row of 50×50 tiles along the bottom
    // For a window of height 600, let's place them at y=55

    // load the background
    bground.setParams({ 0.f,0.f }, { 3200.f, 1800.f }, Cfg::Textures::BGSTART_BIG, 0, 1);

    gameView = wnd_.getDefaultView();
}

void SandboxState::ProcessInputStates()
{

    

    // now handle those buttons
    player.processInput();


    // now player is in ausable state for this frame

    //bool jumping = false;
    //bool justJumped = false;
    //bool startedFalling = false;
    //bool falling = false;

    //if (player.oldVelocity.y < 0.f)
    //{
    //    jumping = true;
    //    player.oldVelocity.y *= 0.9899f;
    //    if (player.oldVelocity.y >= -1.f)
    //    {
    //        player.oldVelocity.y = 0.f;
    //        jumping = false;
    //        startedFalling = true;
    //    }

    //}
    //
    //if (player.tempVelocity.y > 0.f)
    //{
    //    falling = true;
    //}
    //player.tempVelocity = { 0.f, 0.f };
    //if (!jumping && !falling)
    //{

    //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && player.oldVelocity.y == 0.f && !startedFalling)
    //    {
    //        if (player.getCurrID() != "Jump")
    //        {
    //            jumping = true;
    //            justJumped = true;
    //            player.setAnimation("Jump");
    //            
    //            player.oldVelocity.y = -1300.f;
    //        }
    //    }
    //}


    //// e.g. read keyboard states, handle commands, etc.
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    //{
    //    if (!jumping && !falling)
    //    {
    //        if (player.getCurrID() != "Walk")
    //        {
    //            player.setAnimation("Walk");
    //        }


    //        if (player.getCurrentIndex() == 0)
    //            player.tempVelocity.x = -60.f;
    //        else if (player.getCurrentIndex() == 1)
    //            player.tempVelocity.x = -150.f;
    //        else
    //            player.tempVelocity.x = -300.f;
    //    }
    //    else
    //    {
    //        player.tempVelocity.x = -300.f;
    //    }

    //    if (player.getCurrDir() != "Left")
    //    {
    //        player.setCurrDir("Left");
    //    }
    //}

    //// e.g. read keyboard states, handle commands, etc.
  

   

    //// e.g. read keyboard states, handle commands, etc.
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    //{
    //    if (!jumping && !falling)
    //    {
    //        if (player.getCurrID() != "Walk")
    //        {
    //            player.setAnimation("Walk");
    //        }


    //        if (player.getCurrentIndex() == 0)
    //            player.tempVelocity.x = 60.f;
    //        else if (player.getCurrentIndex() == 1)
    //            player.tempVelocity.x = 150.f;
    //        else
    //            player.tempVelocity.x = 300.f;
    //    }
    //    else
    //    {
    //        player.tempVelocity.x = 300.f;
    //    }
    //    
    //    if (player.getCurrDir() != "Right")
    //    {
    //        player.setCurrDir("Right");
    //    }
    //}

    //if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
    //    (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
    //{
    //    if (player.getCurrID() != "Idle")
    //    {
    //        player.setAnimation("Idle");
    //    }
    //  
    //    player.tempVelocity.x = 0.f;
    //}

    //// ADD GRAVITY EVERY TURN
    //if (!jumping || (player.oldVelocity.y == 0.f && jumping))
    //{
    //    player.tempVelocity.y = 400.f;
    //   
    //}
    //else
    //{
    //        player.tempVelocity.y = player.oldVelocity.y; // -1 * (abs(player.currVelocity().y) * 0.9998f);
    //    
    //}



    
}

void SandboxState::Update(float dt_, sf::RenderWindow& wnd_)
{

    bground.update(dt_);
    
    // Move the player

    player.Update(dt_);
    std::vector<std::pair<StaticObject*, float>> z;
    z.clear();
    z.reserve(tilemap.getTiles().size());
    for (auto& statObj : tilemap.getTiles())
    {
        if (statObj.getSolid() == false) { continue; }
        float len = -1.f;
        bool collided = Physics::checkCollision(&player, &statObj, len);
        if (collided)
        {
            z.emplace_back(std::pair{&statObj, len});
        }
    }
    z.shrink_to_fit();

    std::sort(z.begin(), z.end(), [&](const std::pair<StaticObject*,float>& a, const std::pair<StaticObject*, float>& b) 
        {
            return a.second < b.second;
        });

    for (int i =0; i < z.size(); i++)
    {
        Physics::resolveCollision(&player, z[i].first);

        //player.posx = player.tempPosition.x;
        //player.posy = player.tempPosition.y;
    }
   


    // Print position for debug
    //std::cout << "Player pos: (" << player.posx << ", " << player.posy << ")\n";
}

void SandboxState::UpdateFixed(float dt_)
{

    

    // Physics updates
    player.FixedUpdate(dt_);

}

void SandboxState::Render(sf::RenderWindow& wnd_)
{
    // Draw static objects’ bounding boxes
    //for (auto& statObj : tilemap.getTiles())
    //{
    //    sf::RectangleShape wallRect;
    //    wallRect.setPosition(statObj.posx, statObj.posy);
    //    wallRect.setSize({ statObj.getBBox().width, statObj.getBBox().height });
    //    wallRect.setFillColor(sf::Color::Red);
    //    wnd_.draw(wallRect);
    //}
 



    // now things are situated, lets update the gameView
    if (wnd_.mapCoordsToPixel({ player.posx, player.posy }).x >= 550 && player.currVelocity().x > 0.f)
    {
        gameView.setCenter({ player.posx - 150.f, gameView.getCenter().y });
        if (gameView.getCenter().x + 400 > tilemap.pitch() * tilemap.getTiles()[0].texRect().width)
        {
            gameView.setCenter({ tilemap.pitch() * tilemap.getTiles()[0].texRect().width - 400.f, gameView.getCenter().y });
        }
    }
    else if (wnd_.mapCoordsToPixel({ player.posx, player.posy }).x <= 200 && player.currVelocity().x < 0.f)
    {

        gameView.setCenter({ player.posx + 200.f, gameView.getCenter().y });
        if (gameView.getCenter().x - 400 < 0)
        {
            gameView.setCenter({ 400.f, gameView.getCenter().y });
        }
    }
    wnd_.setView(gameView);

    bground.render(wnd_, getViewBounds(gameView));

    tilemap.Render(wnd_);

    wnd_.draw(*player.getSprite());
}

sf::View& SandboxState::gameViewRef()
{
    return gameView;
}

sf::FloatRect SandboxState::getViewBounds(const sf::View& view)
{
        sf::Vector2f size = view.getSize();
        sf::Vector2f center = view.getCenter();
        // The view’s origin is at (center.x - size.x/2, center.y - size.y/2)
        return sf::FloatRect(center.x - size.x * 0.5f,
            center.y - size.y * 0.5f,
            size.x,
            size.y);
}
