#include "Background.h"
#include <iostream>
void Background::setParams(sf::Vector2f pos_, sf::Vector2f size_, Cfg::Textures texID_, int layer_, int level_)
{

	if (layer_ < (int)texID.size() - 1)
	{
		auto sz = positions[layer_].size();
		if (sz == 1)
		{
			positions[layer_][0] = sf::Vector2f{ pos_ };
			positions[layer_].push_back(sf::Vector2f{ pos_.x + sizes[layer_].x, pos_.y });
		}
		else
		{
			positions[layer_].push_back(sf::Vector2f{ pos_.x , pos_.y });
			positions[layer_].push_back(sf::Vector2f{ pos_.x + sizes[layer_].x, pos_.y });
		}
		/*positions[layer_][0] = pos_;
		positions[layer_][1] =  {pos_.x + sizes[layer_].x, pos_.y };*/
		sizes[layer_] = size_;
		texID[layer_] = texID_;
		
	}
	else {
		positions.push_back(std::vector<sf::Vector2f>{});
		positions[0].clear();
		if (positions[0].empty())
		{
			positions[0].push_back(sf::Vector2f{ pos_ });
			positions[0].push_back(sf::Vector2f{ pos_ });
		}
		else
		{
			auto sz = positions[0].size();
			if (sz == 1)
			{
				positions[0][0] = sf::Vector2f{ pos_ };
				positions[0].push_back(sf::Vector2f{ pos_ });
			}
		}

		//positions[positions.size() - 1].push_back({ pos_.x , pos_.y });
		//positions[positions.size() - 1].push_back({ pos_.x + sizes[layer_].x, pos_.y });
		if (sizes.size() == 1)
			sizes[0] = size_;
		else
			sizes.push_back(size_);
	
		if (texID.size() == 1)
			texID[0] = texID_;
		else
			texID.push_back(texID_);
	}

	setLevel(level_);
}

void Background::setLevel(int lvlNum)
{
	//back layer
	if (positions.size() > 0)
	{
		positions[0][0] = {0.f, -1200.f};
		positions[0][1] = { sizes[0].x, -1200.f};
		isBGCopyBehind = true;

	}

	// mid layer
	if (positions.size() > 1)
	{
		if (!positions[1].empty()) {
			positions[1][0] = { 0.f, 0.f };
			positions[1][1] = { 0.f, 0.f };
		}
	
	}

	// layer on bg closest to the back side of player
	if (positions.size() > 2)
	{
		if (!positions[2].empty())
		{
			positions[2][0] = { 0.f,0.f };
			positions[2][1] = { 0.f,0.f };
		}

	}
}

void Background::update(float dt_)
{
	//if (positions.size() > 0)
	//{
	//	positions[0] = { positions[0].x - 5.f * dt_, positions[0].y };
	//	//positions[0] = { 0.f, -1200.f };
	//}

	//// mid layer
	//if (positions.size() > 1)
	//{
	//	positions[1] = { 0.f, 0.f };
	//}

	//// layer on bg closest to the back side of player
	//if (positions.size() > 2)
	//{
	//	positions[2] = { 0.f,0.f };
	//}
	if (this->isBGCopyBehind)
		positions[0][0] = { positions[0][0].x - 500.f * dt_, positions[0][0].y };
	else
		positions[0][1] = { positions[0][1].x - 500.f * dt_, positions[0][1].y };




}

void Background::render(sf::RenderWindow& wnd_, sf::FloatRect viewBounds)
{
	

	if (this->isBGCopyBehind)
	{
		positions[0][1] = { positions[0][0].x + sizes[currentLevel].x, positions[0][0].y };
	}
	else
	{
		positions[0][0] = { positions[0][1].x + sizes[currentLevel].x, positions[0][1].y };
	}



	float left = (wnd_.getView().getCenter().x - 400.f); // vector magnitude from start X to current X left side of screen
	if (isBGCopyBehind == true)
	{
		if (positions[0][0].x <= left - sizes[0].x )
		{
			std::cout << "copy now in front" << std::endl;
			this->isBGCopyBehind = false;
			positions[0][0].x = positions[0][1].x + sizes[0].x;
		}
	}
	else if (isBGCopyBehind == false)
	{
		if (positions[0][1].x <= left - sizes[0].x )
		{
			std::cout << "copy now in back" << std::endl;

			this->isBGCopyBehind = true;
			positions[0][1].x = positions[0][0].x + sizes[0].x;
		}
	}
	//if (diff + 800.f >= sizes[0].x / 2.f + sizes[0].x - 800.f)
	//{
	//	isBGCopyBehind = false;
	//	positions[0][0].x = positions[0][1].x + sizes[0].x;
	//}
	//else if (diff + 800.f >= sizes[0].x * 2.f - 800.f)
	//{
	//	isBGCopyBehind = true;
	//	positions[0][0].x = wnd_.getView().getCenter().x - 400.f - sizes[0].x + 800.f;
	//	positions[0][1].x = positions[0][0].x + sizes[0].x;
	//}
		

	if (texID.size() == 0) { return; }

	if (texID.size() > 0) {
		sf::FloatRect backgroundRect = {};
		if (isBGCopyBehind == true)
			backgroundRect = sf::FloatRect(positions[0][0].x, positions[0][0].y, sizes[0].x * 2.f, sizes[0].y);
		else
			backgroundRect = sf::FloatRect(positions[0][1].x, positions[0][1].y, sizes[0].x * 2.f, sizes[0].y);


		sf::FloatRect intersection;
		if (viewBounds.intersects(backgroundRect, intersection))
		{
			if (isBGCopyBehind == true)
			{
				// There's an overlap
				sf::Sprite bgLayer0 = {};
				bgLayer0.setTexture(Cfg::textures.get((int)texID[0]));
				bgLayer0.setTextureRect({ sf::Vector2i({(int)abs(positions[0][0].x) + (int)(wnd_.getView().getCenter().x - 400.f),
					(int)abs(positions[0][0].y)}),{(int)(std::max(800.f - (sizes[0].x - wnd_.getView().getCenter().x), 800.f)),
					sf::IntRect(intersection).height} });
				bgLayer0.setPosition(sf::Vector2f({ (wnd_.getView().getCenter().x - 400.f), (wnd_.getView().getCenter().y - 300.f) }));
				wnd_.draw(bgLayer0);
			
				sf::Sprite bgLayerCopy0 = {};
				bgLayerCopy0.setTexture(Cfg::textures.get((int)texID[0]));
				bgLayerCopy0.setTextureRect({ sf::Vector2i({(int)((int)abs(positions[0][1].x) - (int)sizes[0].x) + (int)(wnd_.getView().getCenter().x - 400.f) + (int)abs(positions[0][0].x),
					(int)(abs(positions[0][0].y))}),{ 800 - (int)(std::max(800.f - (sizes[0].x - wnd_.getView().getCenter().x), 0.f)),
					sf::IntRect(intersection).height} });
				bgLayerCopy0.setPosition(sf::Vector2f({ ( positions[0][0].x + sizes[0].x), (bgLayer0.getPosition().y)}));
				wnd_.draw(bgLayerCopy0);
			}
			else
			{
				// There's an overlap
				sf::Sprite bgLayer0 = {};
				bgLayer0.setTexture(Cfg::textures.get((int)texID[0]));
				bgLayer0.setTextureRect({ sf::Vector2i({(int)abs(positions[0][1].x) + (int)(wnd_.getView().getCenter().x - 400.f),
					(int)abs(positions[0][1].y)}),{(int)(std::max(800.f - (sizes[0].x - wnd_.getView().getCenter().x), 800.f)),
					sf::IntRect(intersection).height} });
				bgLayer0.setPosition(sf::Vector2f({ (wnd_.getView().getCenter().x - 400.f), (wnd_.getView().getCenter().y - 300.f) }));
				wnd_.draw(bgLayer0);

				sf::Sprite bgLayerCopy0 = {};
				bgLayerCopy0.setTexture(Cfg::textures.get((int)texID[0]));
				bgLayerCopy0.setTextureRect({ sf::Vector2i({(int)((int)abs(positions[0][0].x) - (int)sizes[0].x) + (int)(wnd_.getView().getCenter().x - 400.f) + (int)abs(positions[0][1].x),
					(int)(abs(positions[0][1].y))}),{ 800 - (int)(std::max(800.f - (sizes[0].x - wnd_.getView().getCenter().x), 0.f)),
					sf::IntRect(intersection).height} });
				bgLayerCopy0.setPosition(sf::Vector2f({ (positions[0][0].x + sizes[0].x), (bgLayer0.getPosition().y) }));
				wnd_.draw(bgLayerCopy0);
			}


		}
		else
		{
			// No overlap, so skip drawing
			return;
		}

		
		
	} 
	if (texID.size() > 1)
	{
		sf::Sprite bgLayer1 = {};
		bgLayer1.setTexture(Cfg::textures.get((int)texID[1]));
		bgLayer1.setPosition(positions[1][0]);
		wnd_.draw(bgLayer1);
	}
	if (texID.size() > 2)
	{
		sf::Sprite bgLayer2 = {};
		bgLayer2.setTexture(Cfg::textures.get((int)texID[2]));
		bgLayer2.setPosition(positions[2][0]);
		wnd_.draw(bgLayer2);
	}

	
}
