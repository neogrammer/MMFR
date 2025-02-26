#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <Resources/Maps.h>
#include <string>
#include <iostream>
struct AnimFrame;
class GameObject;
class Animator
{
	GameObject* owner;
	AnimMap animMap;
	std::string currAnimID{ "Invariant" };
	std::string tempAnimID{ "Invariant" };
	std::string currAnimDir{ "Invariant" };
	std::string tempAnimDir{ "Invariant" };
	float currFrameElapsed{0.f};
	float currLoopWaitElapsed{ 0.f };

public:
	Animator(GameObject* owner_);
	~Animator() {}
	Cfg::Textures getCurrTexID() const { return animMap.at(currAnimID).at(currAnimDir).get()->getTexID(); }

	void Update(float dt_);
	inline int getCurrIndex() const 
	{ 
		return animMap.at(currAnimID).at(currAnimDir)->currIndex;
	}
	inline std::string getCurrAnimID() const { return currAnimID; }
	inline std::string getCurrAnimDir() const { return currAnimDir; }
	inline void setCurrIndex(int num_) { animMap.at(currAnimID).at(currAnimDir)->currIndex = num_; }
	inline void setCurrAnimID(std::string id_){ tempAnimID = id_; }
	inline void setCurrAnimDir(std::string dir_) {  tempAnimDir = dir_; }
	inline Animation& getAnimation() { return *animMap.at(currAnimID).at(currAnimDir); };
	inline const sf::IntRect& getCurrFrame() const 
	{
		return animMap.at(currAnimID).at(currAnimDir)->frames.at(getCurrIndex()).textureRect;
	}
	sf::Vector2f getCurrOffset() const;
	
	inline Cfg::Textures  getCurrID() const 
	{
		return animMap.at(currAnimID).at(currAnimDir)->frames.at(getCurrIndex()).textureID;
	}
	inline const sf::IntRect& getFrame(std::string id_, std::string dir_, int frame_) const
	{
		if (animMap.find(id_) == animMap.end() || animMap.at(id_).find(dir_) == animMap.at(id_).end() || frame_ < 0 || frame_ >= animMap.at(id_).at(dir_)->frames.size())
		{
			std::cout << "Unable to find that combination of keys in the anim map" << std::endl;
			throw std::runtime_error("Unable to find that combination of keys in the anim map");
		}
		return animMap.at(id_).at(dir_)->frames[frame_].textureRect;
	}

	void addAnimation(std::string id_, std::string dir_, sf::Vector2f frameSize_, sf::Vector2f startPos_, int numFrames_, Cfg::Textures texID_, float frameDelay_, float loopWait_);
	void addAnimFrame(std::vector<AnimFrame>& frames_, sf::IntRect rect_, Cfg::Textures texID_);

};