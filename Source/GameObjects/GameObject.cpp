#include "GameObject.h"

GameObject::GameObject(std::string filename_, float x_, float y_ )
	: posx{x_}
	, posy{ y_ }
{
	bboxMap.clear();
	bboxMap.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<BBox>>>{"Invariant", std::unordered_map<std::string, std::vector<BBox>>{}});
	bboxMap.at("Invariant").clear();
	bboxMap.at("Invariant").emplace(std::pair<std::string, std::vector<BBox>>{ std::pair<std::string, std::vector<BBox>>{"Invariant", std::vector<BBox>{}}});
	bboxMap.at("Invariant").at("Invariant").clear();
	bboxMap.at("Invariant").at("Invariant").emplace_back(BBox{this});

}

GameObject::~GameObject()
{

}

void GameObject::addBBox(std::string id_, std::string dir_, sf::FloatRect bbox_)
{
	if (bboxMap.find(id_) == bboxMap.end())
	{
		bboxMap[id_] = std::unordered_map<std::string, std::vector<BBox>>{};
		bboxMap[id_].clear();
	}
	if (bboxMap.at(id_).find(dir_) == bboxMap.at(id_).end())
	{
		bboxMap[id_].emplace(std::pair<std::string, std::vector<BBox>>{dir_, std::vector<BBox>{}});
		bboxMap[id_].at(dir_).clear();
	}

	bboxMap[id_].at(dir_).emplace_back(this, bbox_.left, bbox_.top, bbox_.width, bbox_.height);

}

BBox& GameObject::getBBox()
{
	// TODO: insert return statement herereturn bboxMap.at(id_).at(dir_).at(index_);

	return bboxMap.at("Invariant").at("Invariant").at(0);
}

BBox& GameObject::getBBox(std::string id_, std::string dir_, int index_)
{
	return bboxMap.at(id_).at(dir_).at(index_);
}

std::string GameObject::getCurrID()
{
	return currID;
}

std::string GameObject::getCurrDir()
{
	return currDir;
}

