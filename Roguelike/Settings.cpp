#include "Settings.h"

namespace Roguelike
{
	Settings::Settings()
	{
		resourcesPath = "Resources\\";
		soundPath = resourcesPath + "Sounds\\";
		fontPath = resourcesPath + "Fonts\\";
		texturePath = resourcesPath + "Textures\\";
		textureMapsPath = resourcesPath + "TextureMaps\\";

		screenWidth = 1280;
		screenHeight = 720;
		gameName = L"Roguelike";
		playerSize = 32.f;
		mapTileSize = 36.f;
	}

	MaxrEngine::Vector2Df Settings::ScreenCenter()
	{
		return ScreenSize() * 0.5f;
	}

	MaxrEngine::Vector2Df Settings::ScreenSize()
	{
		return 	MaxrEngine::Vector2Df({static_cast<float>(screenWidth), static_cast<float>(screenHeight)});
	}
}
