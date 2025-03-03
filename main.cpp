#include <SFML/Graphics.hpp>
#include "Resources/Cfg.h"
#include "SandboxState.h"

#include <optional>
#include <utility>
#include <memory>

sf::Clock gtimer{};
std::unique_ptr<SandboxState> sboxState;

int UnloadProgram();
int InitProgram();
int HandleEvent(const std::optional<sf::Event> evt_);
int ProcessStateInput(float gameTime_);
int Update(float gameTime_, sf::RenderWindow& wnd_);
void UpdateFixed(float gameTime_);
int RenderScene(sf::RenderWindow& wnd_);

int main(int argc, char* argv[])
{
	Cfg::Initialize();

	
	sf::RenderWindow gwnd(sf::VideoMode({ 800, 600 }), "My window", sf::Style::None);
	sboxState = std::make_unique<SandboxState>(gwnd);

	int result = InitProgram();

	if (result >= 0) { return result; }
	

	// We'll run the game at a stable 1/60 for physics
	const float FIXED_DELTA = 1.0f / 60.0f; // ~0.0166667
	float accumulator = 0.0f;
	
	while (gwnd.isOpen())
	{
		sf::Event e;
		while (gwnd.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
			{
				gwnd.close();
			}
				break;
			case sf::Event::KeyReleased:
			{
				if (e.key.code == sf::Keyboard::Escape)
					gwnd.close();
			}
				break;
			default:
				break;
			}
		}
		auto gameTime = gtimer.restart().asSeconds();
		if (gameTime > 0.1f)
		{
			gameTime = 0.1f;
		}
		accumulator += gameTime;
		if (gwnd.isOpen())
		{
			result = ProcessStateInput(gameTime);
			if (result >= 0) { return result; }
		
			while (accumulator >= FIXED_DELTA)
			{
				UpdateFixed(FIXED_DELTA);
				if (result >= 0) { return result; }
				accumulator -= FIXED_DELTA;
			}

			result = Update(gameTime, gwnd);
			if (result >= 0) { return result; }

			result = RenderScene(gwnd);
			if (result >= 0) { return result; }
		}
	}
	result = UnloadProgram();
	
	
	if (result >= 0)
		return result;
	else
		return 143;

}

/// <summary>
/// This is for loading initial assets and stuff in Cfg::
/// </summary>
/// <returns></returns>
int InitProgram()
{
	Cfg::Initialize();
	gtimer.restart();
	return -1;
}

int HandleEvent(const std::optional<sf::Event> evt_)
{
	return -2;
}

int ProcessStateInput(float gameTime_)
{
	sboxState->ProcessInputStates();
	return -3;
}

int Update(float gameTime_, sf::RenderWindow& wnd_)
{
	sboxState->Update(gameTime_, wnd_);
	return -4;
}

void UpdateFixed(float gameTime_)
{
	sboxState->UpdateFixed(gameTime_);
}

int RenderScene(sf::RenderWindow& wnd_)
{
	wnd_.clear(sf::Color::Blue);

	sboxState->Render(wnd_);

	wnd_.display();
	return -5;
}

int UnloadProgram()
{
	// delete any heap variables for main program or global
	Cfg::Uninitialize();
	return -6;
}