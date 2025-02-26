#include "BBox.h"
#include <assert.h>
#include <GameObjects/GameObject.h>
BBox::BBox(GameObject* owner_, float offx_, float offy_, float width_, float height_)
	: owner(owner_)
	, offx{offx_}
	, offy{offy_}
	, width{width_}
	, height{height_}
{
	assert(owner != nullptr);
}

BBox::~BBox()
{
}

