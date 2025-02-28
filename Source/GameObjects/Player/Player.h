#pragma once
#include <GameObjects/DynamicObject.h>
#include "Animation/Animator.h"
#include <FSM/PlayerAnimFSM.h>

class Player : public DynamicObject
{
	bool jumpHeld{false};
	bool jumpDown{ false };
	bool jumpPressed{ false };
	bool rightHeld{false};
	bool rightDown{ false };
	bool rightPressed{ false };
	bool leftHeld{ false };
	bool leftDown{ false };
	bool leftPressed{false};
	bool canJump{ false };
	FSM_Player animFSM;
public:
	Player();
	~Player();
	void FixedUpdate(float fps60_) override;
	void Update(float dt_) override;
	std::unique_ptr<sf::Sprite> getSprite();
	std::string getAnimationID();
	Animation& getAnimation();

	void Land();
	void syncAnimState();
	void setAnimation(std::string animID);
	void setCurrDir(std::string dir_);
	void processInput();
	bool getJumpDown();
	bool getLeftDown();
	bool getRightDown();
	void setJumpDown(bool cond_);
	void setLeftDown(bool cond_);
	void setRightDown(bool cond_);
	bool getJumpPressed();
	bool getLeftPressed();
	bool getRightPressed();
	bool getJumpHeld();
	bool getLeftHeld();
	bool getRightHeld ();
	bool getCanjump();
	void setCanJump(bool cond_);



};