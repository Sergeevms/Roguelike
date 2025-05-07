#pragma once
#include "Scene.h"
#include <memory>
#include "Player.h"
#include "Wall.h"
#include "Floor.h"
#include "Labyrinth.h"


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
		std::shared_ptr<Wall> testWall;
		std::shared_ptr<Floor> testFloor;
		std::shared_ptr<Labyrinth> labyrinth;
	};

}
