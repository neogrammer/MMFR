#pragma once
#include <Physics/BBox.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <Resources/Maps.h>
#include <SFML/Graphics/RenderWindow.hpp>


class GameObject
{
	std::string currID{"Invariant"};
	std::string currDir{"Invariant"};

public:
	float posx{0}, posy{0};
	
	

	BBMap bboxMap;
	GameObject(std::string filename_, float x_ = 0.f, float y_ = 0.f);
	virtual ~GameObject() = 0;

	virtual void Update(float dt_)
	{
		// Default implementation (optional).
		// Often empty if the base class doesn't need to do anything here.
	}
	void addBBox(std::string id_, std::string dir_, sf::FloatRect bbox_);

	// Called in a fixed-step loop (e.g. 60Hz).
	// Typically for physics or collision checks.
	virtual void FixedUpdate(float fps60_)
	{
		// Default implementation (optional).
	}

	virtual void Render(sf::RenderWindow& wnd_) {}

	virtual BBox& getBBox(); // current
	virtual BBox& getBBox(std::string id_, std::string dir_, int index_);
	virtual std::string getCurrID();
	virtual std::string getCurrDir();
	inline const std::string& getCurrDir() const { return currDir; }

};