#include "pch.h"
#include "RenderSystem.h"

namespace MaxrEngine
{
	RenderSystem* RenderSystem::Instance()
	{
		static RenderSystem render;
		return &render;
	}

	void RenderSystem::SetMainWindow(sf::RenderWindow* newWindow)
	{
		window = newWindow;
	}

	sf::RenderWindow& RenderSystem::GetMainWindow() const
	{
		return *window;
	}

	sf::RenderWindow& RenderSystem::CrateMainWindow(const sf::VideoMode mode, sf::String title)
	{
		window = new sf::RenderWindow(mode, title);
		return *window;
	}

	void RenderSystem::Render(const sf::Drawable& drawable)
	{
		window->draw(drawable);
	}
}