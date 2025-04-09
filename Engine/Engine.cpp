#include "pch.h"
#include "Engine.h"
#include <iostream>

namespace MaxrEngine
{
	Engine::Engine()
	{
	}

	void Engine::Initialize()
	{
		std::cout << "Движок инциализирован" << std::endl;
	}

	void Engine::Run()
	{
		std::cout << "Движок запущен!" << std::endl;
	}
}
