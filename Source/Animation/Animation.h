#pragma once

#include <Animation/AnimFrame.h>
#include <vector>
#include <string>
#include <Resources/Cfg.h>

class Animation
{
	friend class Animator;

	std::string name{ "Invariant" };
	std::string dir{ "Invariant" };
	int currIndex{ 0 };

	Cfg::Textures textureID{ Cfg::Textures::Invariant };

	float frameDelay{ 0.f };
	float loopDelay{ 0.f };
	float startDelay{ 0.f };

	bool playing{ true };
	bool looping{ true };
	bool startedLoopWaiting{ false };
	bool currentlyLoopWaiting{ false };
	bool waitingForStartDelay{ false };


	// texRect, texOffset, Cfg::Textures
	std::vector<AnimFrame> frames;

public:
	Animation();
	Animation(Cfg::Textures tex_, std::string name_, std::string dir_, float frameDelay_, float loopDelay_, bool looping_);

	Animation(const Animation&) = delete;
	Animation& operator=(const Animation&) = delete;

	Animation(Animation&&) = default;
	Animation& operator=(Animation&&) = default;
	void addFrame(sf::IntRect rect_, Cfg::Textures texID_);


	void animate(float& loopWaitElapsed, float& frameDelayElapsed);


	inline void setStartingLoopDelay(bool cond_)
	{
		startedLoopWaiting = cond_;
	}

	inline const sf::IntRect& getTexRect() const
	{
		return frames[currIndex].textureRect;
	}


	inline Cfg::Textures getTexID() const
	{
		return frames[currIndex].textureID;
	}

	inline int getCurrIndex() const
	{
		return currIndex;
	}

	inline const std::string& getName()
	{
		return name;
	}

	inline const std::string& getDir()
	{
		return dir;
	}

	inline float getFrameDelay() const
	{
		return frameDelay;
	}

	inline float getLoopDelay() const
	{
		return loopDelay;
	}

	inline float getStartDelay() const
	{
		return startDelay;
	}

	inline bool isWaitingForStartDelay() const
	{
		return waitingForStartDelay;
	}
	
	inline bool isCurrentlyLoopWaiting() const
	{
		return currentlyLoopWaiting;
	}
	
	inline bool doesLoopWait() const
	{
		return (loopDelay > 0.f);
	}

	inline bool hasStartDelay() const
	{
		return (startDelay > 0.f);
	}

	inline bool isLooping() const
	{
		return looping;
	}

	inline bool isPlaying() const
	{
		return playing;
	}

	inline void setLooping(bool cond_)
	{
		looping = cond_;
	}

	inline void play()
	{
		playing = true;
	}

	inline void restart()
	{
		playing = true;
		currIndex = 0;
	}

	inline void pause()
	{
		playing = false;
	}

	inline void stop()
	{
		playing = false;
		currIndex = 0;
	}

	inline void resume()
	{
		playing = true;
	}

	inline void setCurrIndex(int index_) { currIndex = index_; }

};