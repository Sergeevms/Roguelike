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

		enemySpeed = playerSpeed / 2.f;
		enemyVisionRadius = 300.f;
		enemyVisionAngle = 145.f;
		enemySenseRadius = 150.f;
		enemyChaseMaxRadius = enemyVisionRadius;
		enemyChaseMinRadius = 40.f;

		playerHealth = 200.f;
		enemyHealth = 100.f;
		armorDamageReduction = 0.75f;
		atackRange = 100.f;
		atackCooldown = 2.f;
		atackDamage = 30.f;
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
