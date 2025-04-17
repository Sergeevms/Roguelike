#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "RenderSystem.h"
#include "Matrix2D.h"
#include <iostream>
#include <Windows.h>

int main()
{	
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	std::cout << "Test" << std::endl;
	MaxrEngine::RenderSystem::Instance()->CrateMainWindow(sf::VideoMode(1280, 720), "Roguelike");
	MaxrEngine::ResourceSystem::Instance()->LoadTexture("ball", "Resources/Textures/ball.png");

	auto developerLevel = std::make_shared<Roguelike::DeveloperLevel>();
	developerLevel->Start();

	MaxrEngine::Matrix2D identytiMatrix;
	identytiMatrix.Print();
	identytiMatrix.GetInversed().Print();
	(identytiMatrix * identytiMatrix.GetInversed()).Print();

	MaxrEngine::Matrix2D translationMatrix = MaxrEngine::Matrix2D(MaxrEngine::Vector2Df(12.f, 5.f), 0.f, MaxrEngine::Vector2Df(1.f, 1.f));
	translationMatrix.Print();
	translationMatrix.GetInversed().Print();
	(translationMatrix*translationMatrix.GetInversed()).Print();

	MaxrEngine::Matrix2D rotationMatrix = MaxrEngine::Matrix2D(MaxrEngine::Vector2Df(0.f, 0.f), 90.f, MaxrEngine::Vector2Df(1.f, 1.f));
	rotationMatrix.Print();

	(rotationMatrix * translationMatrix).Print();

	MaxrEngine::Matrix2D someMatrix = MaxrEngine::Matrix2D(MaxrEngine::Vector2Df(13.f, 25.f), 90.f, MaxrEngine::Vector2Df(1.5f, 1.f));
	someMatrix.Print();
	someMatrix.GetInversed().Print();

	(someMatrix * someMatrix.GetInversed()).Print();

	MaxrEngine::Engine::Instance()->Run();

	return 0;
}
