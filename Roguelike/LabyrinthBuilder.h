#pragma once
#include <vector>
#include "Wall.h"
#include "Floor.h"
#include "Vector.h"
#include "Labyrinth.h"

namespace Roguelike
{
	enum class TileType;

	class LabyrinthBuilder
	{
	public:
		LabyrinthBuilder();
		//Resets current labyrinth and set new size
		void StartBuilding(MaxrEngine::Vector2Di newTileSize);

		/*Adds Rectangle element (floor surronded by wall) (not bigger than predefined labyrinth tileSize)
		* converts previous placed walls to floor, but not floor to wall
		*/
		void AddRect(MaxrEngine::Vector2Di bottomLeft, MaxrEngine::Vector2Di size);
		//Sets position tile to Wall
		void SetWall(MaxrEngine::Vector2Di position);
		//Sets position tile to Floor
		void SetFloor(MaxrEngine::Vector2Di position);
		//Get current labyrinth tileSize
		MaxrEngine::Vector2Di GetTileSize() const;
		//Constructs Labyrinth object and starts building new labyrinth with the same size
		std::shared_ptr<Labyrinth> ConstructLabyrinth();
	private:
		std::vector<std::vector<TileType>> tileType;
		std::vector<int> usableFloorTextureId;
		//Changes wall TileType according to its position
		void UpdateWallType();
		bool IsWall(MaxrEngine::Vector2Di position);
		MaxrEngine::Vector2Df GetCenterInTyles();
		MaxrEngine::Vector2Df GetTylePosition(MaxrEngine::Vector2Di tilePosition);
	};
}

