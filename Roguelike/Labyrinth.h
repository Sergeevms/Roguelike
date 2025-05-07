#pragma once
#include <vector>
#include "Wall.h"
#include "Floor.h"
#include "GameObject.h"

namespace Roguelike
{
	class Labyrinth
	{
	public:
		Labyrinth();
		MaxrEngine::GameObject* GetGameObject();
		const std::vector<std::shared_ptr<Wall>>& GetWalls() const;
		const std::vector<std::shared_ptr<Floor>>& GetFloors() const;
		void SetCenterPosition(const MaxrEngine::Vector2Df newPosition);
		friend class LabyrinthBuilder;
	private:
		MaxrEngine::GameObject* gameObject;
		std::vector <std::shared_ptr<Wall>> walls;
		std::vector <std::shared_ptr<Floor>> floors;
	};
}

