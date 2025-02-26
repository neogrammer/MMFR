#include <GameObjects/DynamicObject.h>

DynamicObject::DynamicObject(std::string filename_, float x_, float y_)
	: GameObject(filename_, x_, y_)
	, velocity{0.f,0.f}
	, acceleration{0.f,0.f}
	/*, tempPosition{x_, y_}
	, tempVelocity{0.f,0.f}
	, oldPosition{x_, y_}
    , oldVelocity{ 0.f,0.f }*/
    , animator{ this }
{
    // Initialize shape
   // For example, let’s assume getBBox().width/height is valid//
//    auto width = getBBox().width;
  //  auto height = getBBox().height;

  //  shape.setSize({ width, height });
//    shape.setFillColor(sf::Color::Green);     // Just picking a color for clarity
   // shape.setPosition(x_, y_);
}


BBox& DynamicObject::getBBox()
{
    // TODO: insert return statement herereturn bboxMap.at(id_).at(dir_).at(index_);

    return bboxMap.at(animator.getCurrAnimID()).at(animator.getCurrAnimDir()).at(animator.getCurrIndex());
}

DynamicObject::~DynamicObject()
{
}

void DynamicObject::Render(sf::RenderWindow& wnd_)
{
   
}

// Called every display frame
void DynamicObject::Update(float dt_)
{
    // For example, handle user input or do non-physics movement
    // This might be an empty function if you do all movement in FixedUpdate.
    // change tempPosition and tempVelocity only here and acceleration


}

void DynamicObject::FixedUpdate(float fps60_)
{
    //// Example: gather->process->commit approach

    //// 1) Gather old states
    //oldPosition = { posx, posy };
    //oldVelocity = velocity;

    //// 2) Integrate
    //tempPosition = oldPosition + oldVelocity * fps60_;
    //tempVelocity = oldVelocity + acceleration * fps60_;

    //// 3) Collision checks (example only, details omitted)
    ////     Possibly adjust tempPosition or tempVelocity

    //// 4) Commit
    //posx = tempPosition.x;
    //posy = tempPosition.y;
    //velocity = tempVelocity;


    // Sync shape with the new position
   // shape.setPosition(posx, posy);
}