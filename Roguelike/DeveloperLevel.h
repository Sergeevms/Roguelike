#pragma once
#include "Scene.h"
#include <memory>
#include "Player.h"
#include "Labyrinth.h"
#include "BackgroundMusic.h"


namespace Roguelike
{
	class DeveloperLevel :
		public MaxrEngine::Scene
	{
	public:
		virtual void Start() override;
		virtual void Restart() override;
		virtual void Stop() override;
	private:
		std::shared_ptr<Player> player;
		std::shared_ptr<BackgroundMusic> backgroundMusic;
		std::shared_ptr<Labyrinth> labyrinth;
	};

}
