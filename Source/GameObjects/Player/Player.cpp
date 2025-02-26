#include "Player.h"
#include <Physics/Physics.h>
Player::Player()
	: DynamicObject{ "ADDAPLAYERFILE", 200.f,100.f }
{
	// loading in the right facing idle animation frames
	//std::vector<sf::Vector2f> offsets;
	//offsets.clear();
	//offsets.reserve(3);

	for (int i = 0; i < 3; i++)
	{
		//offsets.emplace_back(sf::Vector2f{43.f,68.f});
		addBBox("Idle", "Right", { {43.f,48.f},{56.f,80.f} });
	}
	animator.addAnimation("Idle", "Right", { 130.f,160.f }, { 0.f,160.f }, 3, Cfg::Textures::PlayerAtlas, 0.13f, 2.f );

	//offsets.clear();
	//offsets.reserve(3);

	for (int i = 0; i < 3; i++)
	{
		//offsets.emplace_back(sf::Vector2f{ 38.f,68.f });
		addBBox("Idle", "Left", { {38.f,48.f},{56.f,80.f} });
	}
	animator.addAnimation("Idle", "Left", { 130.f,160.f }, { 0.f,14*160.f }, 3, Cfg::Textures::PlayerAtlas, 0.13f, 2.f);


	//offsets.clear();
	//offsets.reserve(3);

	for (int i = 0; i < 10; i++)
	{
		//offsets.emplace_back(sf::Vector2f{ 43.f,68.f });
		addBBox("Walk", "Right", { {43.f,48.f},{56.f,80.f} });
	}
	animator.addAnimation("Walk", "Right", { 130.f,160.f }, { 2*130.f,2*160.f }, 10, Cfg::Textures::PlayerAtlas, 0.08f, 0.f);


	//offsets.clear();
	//offsets.reserve(3);

	for (int i = 0; i < 10; i++)
	{
		addBBox("Walk", "Left", { {38.f,48.f},{56.f,80.f} });
	}
	animator.addAnimation("Walk", "Left", { 130.f,160.f }, { 2*130.f,15*160.f }, 10, Cfg::Textures::PlayerAtlas, 0.08f, 0.f);

	for (int i = 0; i < 11; i++)
	{
		addBBox("Jump", "Right", { {43.f,48.f},{56.f,80.f} });
	}
	animator.addAnimation("Jump", "Right", { 130.f,160.f }, { 0.f,5*160.f }, 11, Cfg::Textures::PlayerAtlas, 0.13f, 2.f);

	for (int i = 0; i < 11; i++)
	{
		addBBox("Jump", "Left", { {43.f,48.f},{56.f,80.f} });
	}
	animator.addAnimation("Jump", "Left", { 130.f,160.f }, { 0.f,18*160.f }, 11, Cfg::Textures::PlayerAtlas, 0.13f, 2.f);
	animator.setCurrAnimDir("Right");
	animator.setCurrAnimID("Idle");

	this->velocity.y = 400.f;
}

Player::~Player()
{


}

void Player::FixedUpdate(float fps60_)
{
	
	
	DynamicObject::FixedUpdate(fps60_);
	animator.Update(fps60_);
}

void Player::Update(float dt_)
{
	DynamicObject::Update(dt_);

	

	//tempVelocity.y += 400.f * dt_;

	if (jumpDown || rightDown || leftDown)
	{
		// user needs to move
		if (rightPressed || rightDown)
		{
			velocity.x = 300.f;
		}
		if (leftPressed || leftDown)
		{
			velocity.x = -300.f;
		}
	/*	if (jumpPressed && canJump)
		{
			tempVelocity.y = -20000.f;
			canJump = false;
		}*/
	}



	if ((!rightDown && !leftDown) || (rightDown && leftDown))
		velocity.x = 0.f;

	posx += currVelocity().x * dt_;
	posy += currVelocity().y * dt_;
	setVelocity({ currVelocity().x, currVelocity().y + Physics::Gravity * dt_ });

}

std::unique_ptr<sf::Sprite> Player::getSprite()
{
	std::unique_ptr<sf::Sprite> tmp = std::make_unique<sf::Sprite>();
	tmp->setTexture(Cfg::textures.get((int)animator.getCurrTexID()));
	tmp->setTextureRect(animator.getCurrFrame());
	tmp->setPosition({ posx - this->getBBox().offx, posy - this->getBBox().offy });
	return std::move(tmp);
}

std::string Player::getAnimationID()
{
	return animator.getCurrAnimID();
}

Animation& Player::getAnimation()
{
	return animator.getAnimation();
}

void Player::setAnimation(std::string animID)
{
	animator.setCurrAnimID(animID);
}

void Player::setCurrDir(std::string dir_)
{
	if (dir_ != animator.getCurrAnimDir())
	{
		animator.setCurrIndex(0);
		animator.setCurrAnimDir(dir_);
	}
}

void Player::processInput()
{
	// update player button state
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		jumpDown=true;
	}
	else
	{
		jumpDown=false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		leftDown=true;
	}
	else 
	{
		leftDown = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rightDown = true;
	}
	else 
	{
		rightDown = false;
	}

	if (jumpDown)
	{
		if (jumpDown && !jumpPressed && !jumpHeld && canJump)
		{
			jumpPressed = true;
			jumpHeld = false;
			velocity.y = -700.f;
			canJump = false;
		}
		else if (jumpDown && jumpPressed && !jumpHeld)
		{
			jumpHeld = true;
			jumpPressed = false;
		}
		else if (jumpDown && !jumpPressed && jumpHeld)
		{

		}
	}
	else
	{
		jumpPressed = false;
		jumpHeld = false;
	}

	if (rightDown)
	{
		if (rightDown && !rightPressed && !rightHeld)
		{
			rightPressed = true;
			rightHeld = false;
		}
		else if (rightDown && rightPressed && !rightHeld)
		{
			rightHeld = true;
			rightPressed = false;
		}
		else if (rightDown && !rightPressed && rightHeld)
		{

		}
	}
	else
	{
		rightPressed = false;
		rightHeld = false;
	}

	if (leftDown)
	{
		if (leftDown && !leftPressed && !leftHeld)
		{
			leftPressed = true;
			leftHeld = false;
		}
		else if (leftDown && leftPressed && !leftHeld)
		{
			leftHeld = true;
			leftPressed = false;
		}
		else if (leftDown && !leftPressed && leftHeld)
		{

		}
	}
	else
	{
		leftPressed = false;
		leftHeld = false;
	}


	if (jumpPressed)
	{


		if (this->getAnimationID() != "Jump")
		{
			this->setAnimation("Jump");
		}
	}

	else if (leftPressed)
	{
		

		if (this->getAnimationID() != "Walk" || this->getCurrDir() != "Left")
		{
			this->setAnimation("Walk");
		}

		this->setCurrDir("Left");
	}

	else if (rightPressed)
	{


		if (this->getAnimationID() != "Walk" || this->getCurrDir() != "Right")
		{
			this->setAnimation("Walk");
		}

		this->setCurrDir("Right");
	}

	
	else if (!rightDown && !leftDown && canJump)
	{
		if (this->getAnimationID() != "Idle")
		{
			this->setAnimation("Idle");
		}
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (rightDown && !rightPressed)
		{
			rightPressed = true;
		}
		else if (rightDown && rightPressed)
		{
			rightHeld = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (leftDown && !leftPressed)
		{
			leftPressed = true;
		}
		else if (leftDown && leftPressed)
		{
			leftHeld = true;
		}
	}*/
}

bool Player::getJumpDown()
{
	return jumpDown;
}

bool Player::getLeftDown()
{
	return leftDown;
}

bool Player::getRightDown()
{
	return rightDown;
}

void Player::setJumpDown(bool cond_)
{
	jumpDown = cond_;
}

void Player::setLeftDown(bool cond_)
{
	leftDown = cond_;
}

void Player::setRightDown(bool cond_)
{
	rightDown = cond_;
}

bool Player::getJumpPressed()
{
	return jumpPressed;
}

bool Player::getLeftPressed()
{
	return leftPressed;
}

bool Player::getRightPressed()
{
	return rightPressed;
}

bool Player::getJumpHeld()
{
	return jumpHeld;
}

bool Player::getLeftHeld()
{
	return leftHeld;
}

bool Player::getRightHeld()
{
	return rightHeld;
}

bool Player::getCanjump()
{
	return canJump;
}

void Player::setCanJump(bool cond_)
{
	canJump = cond_;
}
