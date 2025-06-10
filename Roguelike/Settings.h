#pragma once
#include "Vector.h"
#include <string>

namespace Roguelike
{
	class Settings
	{
	public:
		static Settings* Instance()
		{
			static Settings world;
			return &world;
		};
		MaxrEngine::Vector2Df ScreenCenter();
		MaxrEngine::Vector2Df ScreenSize();

		//General settings

		int screenWidth;
		int screenHeight;
		std::wstring gameName;

		//Paths to files
		std::string resourcesPath;
		std::string soundPath;
		std::string fontPath;
		std::string texturePath;
		std::string textureMapsPath;

		int playerSize;
		float playerSpeed;
		float enemySpeed;		
		float enemyVisionRadius;
		float enemyVisionAngle;
		float enemySenseRadius;
		float enemyChaseMaxRadius;
		float enemyChaseMinRadius;
		int mapTileSize;

		float playerHealth;
		float enemyHealth;
		float armorDamageReduction;
		float atackRange;
		float atackCooldown;
		float atackDamage;
		
	private:
		Settings();
		~Settings() = default;
		Settings(const Settings&) = delete;
		Settings operator= (const Settings&) = delete;
	};

	enum ActorsGroups
	{
		PlayerGroup,
		EnemyGroup
	};
};