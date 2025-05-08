#include "Labyrinth.h"
#include "GameWorld.h"

namespace Roguelike
{
	Labyrinth::Labyrinth()
	{
		gameObject = MaxrEngine::GameWorld::Instance()->CreateGameObject("Labyrinth");
	}

	MaxrEngine::GameObject* Labyrinth::GetGameObject()
	{
		return gameObject;
	}
	const std::vector<std::shared_ptr<Wall>>& Roguelike::Labyrinth::GetWalls() const
	{
		return walls;
	}

	const std::vector<std::shared_ptr<Floor>>& Labyrinth::GetFloors() const
	{
		return floors;
	}

	void Labyrinth::SetCenterPosition(const MaxrEngine::Vector2Df newPosition)
	{
		auto transform = gameObject->GetComponent<MaxrEngine::TransformComponent>();
		transform->SetWorldPosition(newPosition);
	}
}
