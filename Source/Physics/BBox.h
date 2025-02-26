#pragma once

class GameObject;

class BBox
{
public:
	float offx, offy;
	float width, height;

	GameObject* const owner;
	BBox() = delete;
	BBox(GameObject* owner, float offx_ = 0.f, float offy_ = 0.f, float width_ = 50.f, float height_ = 50.f);
	~BBox();
	BBox(const BBox&) = default;
	BBox& operator=(const BBox&) = default;

	BBox(BBox&&) = default;
	BBox& operator=(BBox&&) = default;

};