#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "ResourceSystem.h"
#include "RenderSystem.h"
#include "DeveloperLevel.h"
#include "Settings.h"
#ifdef CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
#include <iostream>
#include <Windows.h>
#endif // CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT


int main()
{
#ifdef CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	std::cout << "Test" << std::endl;
#endif // CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
	auto settings = Roguelike::Settings::Instance();
	MaxrEngine::RenderSystem::Instance()->CrateMainWindow(sf::VideoMode(settings->screenWidth, settings->screenHeight), settings->gameName);
	MaxrEngine::ResourceSystem::Instance()->LoadTextureMap("PlayerTextures", settings->textureMapsPath + "Player.png", { 48, 63 }, 9, false);
	MaxrEngine::ResourceSystem::Instance()->LoadTextureMap("WallTextures", settings->textureMapsPath + "Wall.png", {16, 16}, 48, false);
	MaxrEngine::ResourceSystem::Instance()->LoadTextureMap("FloorTextures", settings->textureMapsPath + "Floor.png", { 16, 16 }, 49, false);
	MaxrEngine::ResourceSystem::Instance()->LoadTexture("Ball", settings->texturePath + "Ball.png", false);
	MaxrEngine::ResourceSystem::Instance()->LoadMusic("background", "Resources/Sounds/Clinthammer__Background_Music.wav");

	auto developerLevel = std::make_shared<Roguelike::DeveloperLevel>();
	developerLevel->Start();

	MaxrEngine::Engine::Instance()->Run();

	return 0;
}
