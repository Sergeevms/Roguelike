#include "Labyrinth.h"
#include "GameWorld.h"

namespace Roguelike
{
	Labyrinth::Labyrinth() :
		GameObjectContainer("Labyrinth")
	{
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
