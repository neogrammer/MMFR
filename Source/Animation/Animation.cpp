#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(Cfg::Textures tex_, std::string name_, std::string dir_, float frameDelay_, float loopDelay_, bool looping_)
	: textureID{ tex_ }
	, name{ name_ }
	, dir{ dir_ }
	, currIndex{ 0 }
	, frameDelay{ frameDelay_ }
	, loopDelay{ loopDelay_ }
	, looping{ looping_ }
{
}

void Animation::addFrame(sf::IntRect rect_, Cfg::Textures texID_)
{
	frames.emplace_back(rect_, texID_);

}
//
//void Animation::animate()
//{
//	// animator controls how often this is called,
//	// animator must also set currentlyLoopwaiting to false when currentlyLoopWaiting and loopWaitElapsed >= loopDelay
//	// else if not currentlyLoopWaiting, frameelapsed increases and calls animate when passing the delay
//	if (getCurrIndex() < frames.size() - 1)
//	{
//
//		this->setCurrIndex( getCurrIndex() +  1);
//	}
//	else
//	{
//		if (this->looping && this->startedLoopWaiting && !this->currentlyLoopWaiting && this->getLoopDelay() >0.f)
//		{
//			this->currentlyLoopWaiting = true;
//			this->startedLoopWaiting = false;
//		}
//		else if (this->looping && this->currentlyLoopWaiting)
//		{
//
//		}
//		else if (((this->looping && (!this->currentlyLoopWaiting && !this->startedLoopWaiting)) || this->getLoopDelay() == 0.f) && getCurrIndex() >= frames.size() - 1)
//		{
//				this->setCurrIndex(0);
//		}
//		else if (!this->looping)
//		{
//			this->setCurrIndex(((int)frames.size() - 1));
//		}
//		
//	}
//}

void Animation::animate(float& loopWaitElapsed, float& frameDelayElapsed)
{
	if (loopDelay == 0.f)
	{
		// dont sweat loopWaitElapsed, not needed on this one
		if (frameDelayElapsed >= frameDelay)
		{
			currIndex += 1;
			if (looping && currIndex >= frames.size())
			{
				currIndex = 0;
			}
			else if (!looping && currIndex >= frames.size())
			{
				currIndex =(int) frames.size() - 1;
			}
			else
			{

			}
			frameDelayElapsed = 0.f;
		}
	}
	else
	{
		// does loop delay


		if (!currentlyLoopWaiting)
		{
			if (startedLoopWaiting)
			{
				startedLoopWaiting = false;
				currentlyLoopWaiting = true;
			}
		}

		if (currentlyLoopWaiting)
		{
			if (loopWaitElapsed >= loopDelay)
			{
				loopWaitElapsed = 0.f;
				frameDelayElapsed = 0.f;
				currIndex = 0;
				currentlyLoopWaiting = false;
			}
		}
		// dont sweat loopWaitElapsed, not needed on this one
		if (frameDelayElapsed >= frameDelay && !currentlyLoopWaiting)
		{
			frameDelayElapsed = 0.f;
			currIndex += 1;
			if (currIndex >= frames.size())
			{
					startedLoopWaiting = true;
					loopWaitElapsed = 0.f;
					currIndex = (int)frames.size() - 1;
			}
		}
	}
}
