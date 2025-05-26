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
		playerSize = 32;
		playerSpeed = 400.f;
		mapTileSize = 36;

		enemySpeed = 350.f;
		enemyDetectionRadius = 250.f;
		enemyChaseMaxRadius = 250.f;
		enemyChaseMinRadius = 20.f;

		playerHealth = 200;
		enemyHealth = 100;
		armorDamageReduction = 0.75f;
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
