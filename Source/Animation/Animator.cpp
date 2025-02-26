#include <Animation/Animator.h>
#include <memory>
#include <Animation/AnimFrame.h>
#include <GameObjects/GameObject.h>
Animator::Animator(GameObject* owner_)
	: owner{ owner_ }
	, animMap{}
{
	animMap.clear();
	//animMap["Idle"] = std::unordered_map<std::string, std::unique_ptr<Animation>>{};
	//animMap["Idle"].emplace(std::pair{ "Right", std::make_unique<Animation>(Cfg::Textures::PlayerAtlas, "Idle", "Right", 0.13f, 2.f, true)});
	//for (int i = 0; i < 3; i++)
	//{
	//	animMap["Idle"]["Right"]->addFrame(sf::IntRect{ sf::Vector2i(i * 130,1 * 160), sf::Vector2i(130,160) }, sf::Vector2f{0.f,0.f}, Cfg::Textures::PlayerAtlas);
	//}
	//currAnimDir = "Right";
	//currAnimID = "Idle";
	currFrameElapsed = 0.f;
	currLoopWaitElapsed = 0.f;

}

void Animator::Update(float dt_)
{

	bool setCurrIndexToZero = false;
	if (tempAnimID != "Invariant" && tempAnimDir != "Invariant")
	{
		if (tempAnimID != currAnimID)
		{
			currAnimID = tempAnimID;
			setCurrIndexToZero = true;
		}
		if (tempAnimDir != currAnimDir)
		{
			currAnimDir = tempAnimDir;
			setCurrIndexToZero = true;
		}

	}
	auto* anim = animMap.at(currAnimID).at(currAnimDir).get();
	if (setCurrIndexToZero)
		anim->currIndex = 0;

	currLoopWaitElapsed += dt_;
	currFrameElapsed += dt_;
	
	anim->animate(currLoopWaitElapsed, currFrameElapsed);

	//if (anim->currentlyLoopWaiting && anim->loopDelay > 0.f)
	//{
	//	currLoopWaitElapsed += dt_;

	//	if (currLoopWaitElapsed >= anim->getLoopDelay())
	//	{
	//		currLoopWaitElapsed = 0.f;
	//		currFrameElapsed = 0.f;
	//		anim->currentlyLoopWaiting = false;
	//		anim->animate();
	//	}
	//}
	//else
	//{
	//	if (anim->loopDelay == 0.f)
	//		anim->currentlyLoopWaiting = false;

	//	if (anim->isPlaying())
	//	{
	//		currFrameElapsed += dt_;
	//		if (currFrameElapsed >= anim->getFrameDelay())
	//		{
	//			
	//			
	//			if (anim->currIndex >= animMap.at(currAnimID).at(currAnimDir)->frames.size())
	//			{
	//				if (anim->loopDelay > 0.f)
	//				{
	//					anim->currentlyLoopWaiting = true;
	//					//anim->currIndex = (int)animMap.at(currAnimID).at(currAnimDir)->frames.size() - 1;
	//				}
	//			}

	//			//currLoopWaitElapsed = 0.f;
	//			currFrameElapsed = 0.f;
	//			anim->animate();

	//		}
	//	}
	//}
	//

}

sf::Vector2f Animator::getCurrOffset() const
{
	return { owner->getBBox().offx, owner->getBBox().offy };
}

void Animator::addAnimation(std::string id_, std::string dir_, sf::Vector2f frameSize_, sf::Vector2f startPos_, int numFrames_, Cfg::Textures texID_, float frameDelay_, float loopWait_)
{

	if (animMap.find(id_) == animMap.end())
	{
		animMap[id_] = std::unordered_map<std::string, std::unique_ptr<Animation>>{};
	}
	animMap[id_].emplace(std::pair<std::string, std::unique_ptr<Animation>>{dir_, std::make_unique<Animation>(texID_, id_, dir_, frameDelay_, loopWait_, true)});
	for (int i = 0; i < numFrames_; i++)
	{
		animMap[id_][dir_]->addFrame(sf::IntRect{ sf::Vector2i((int)startPos_.x + i * (int)frameSize_.x, (int)startPos_.y), {(int)frameSize_.x, (int)frameSize_.y} }, texID_);
	}
	//if (currAnimID == "Invariant")
	
		currAnimID = id_;
		//if (currAnimDir == "Invariant")
			currAnimDir = dir_;
	


	//if (animMap.find(id_) == animMap.end())
	//{
	//	// not in map lets add it
	//	animMap.emplace(std::pair<std::string, std::unordered_map<std::string, std::unique_ptr<Animation>>>{id_, std::unordered_map<std::string, std::unique_ptr<Animation>>{} });
	//}
	//if (animMap.at(id_).find(dir_) == animMap.at(id_).end())
	//{
	//	animMap.at(id_).emplace(std::pair<std::string, std::unique_ptr<Animation>>{dir_, std::unique_ptr<Animation>{}});
	//	animMap.at(id_)[dir_] = std::make_unique<Animation>();
	//}
	//	

	//	
	//
	//auto* anim = animMap.at(id_).at(dir_).get();
	//anim->frames.clear();
	//anim->frames.reserve(numFrames_);
	//for (int i = 0; i < numFrames_; i++)
	//{
	//	animMap.at(id_)[dir_]->addFrame(sf::IntRect({ i * (int)startPos_.x, (int)startPos_.y }, { (int)frameSize_.x,(int)frameSize_.y }), offsets_.at(i), texID_);
	//	//anim->frames.emplace_back(sf::IntRect({ i * (int)startPos_.x, (int)startPos_.y }, { (int)frameSize_.x,(int)frameSize_.y }), offsets_.at(i), texID_);
	//}
}

void Animator::addAnimFrame(std::vector<AnimFrame>& frames_, sf::IntRect rect_, Cfg::Textures texID_)
{
	frames_.emplace_back(AnimFrame{ rect_, texID_ });
}



