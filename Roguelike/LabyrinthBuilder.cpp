#include "LabyrinthBuilder.h"
#include "Utility.h"
#include "Settings.h"

namespace Roguelike
{
	enum class TileType
	{
		Empty,
		Floor,
		Wall,
		VerticalWall,
		HorizontalWall
	};

	LabyrinthBuilder::LabyrinthBuilder()
	{
		usableFloorTextureId.push_back(0);
		usableFloorTextureId.push_back(1);
		usableFloorTextureId.push_back(2);
		usableFloorTextureId.push_back(8);
		usableFloorTextureId.push_back(10);
	}

	void LabyrinthBuilder::StartBuilding(MaxrEngine::Vector2Di newTileSize)
	{
		tileType = std::vector<std::vector<TileType>>(newTileSize.x, std::vector<TileType>(newTileSize.y, TileType::Empty));
	}

	void Roguelike::LabyrinthBuilder::AddRect(MaxrEngine::Vector2Di bottomLeft, MaxrEngine::Vector2Di size)
	{
		bottomLeft.x = std::clamp(bottomLeft.x, 0, GetTileSize().x);
		bottomLeft.y = std::clamp(bottomLeft.y, 0, GetTileSize().y);
		size.x = std::clamp(size.x, 0, GetTileSize().x - bottomLeft.x);
		size.y = std::clamp(size.y, 0, GetTileSize().y - bottomLeft.y);

		for (int i = bottomLeft.x; i < bottomLeft.x + size.x; ++i)
		{
			for (int j = bottomLeft.y; j < bottomLeft.y + size.y; ++j)
			{
				if (tileType[i][j] == TileType::Empty || tileType[i][j] == TileType::Wall)
				{
					if (i == bottomLeft.x || i == bottomLeft.x + size.x - 1
						|| j == bottomLeft.y || j == bottomLeft.y + size.y - 1)
					{
						tileType[i][j] = TileType::Wall;
					}
					else
					{
						tileType[i][j] = TileType::Floor;
					}
				}
			}
		}
	}

	void LabyrinthBuilder::SetWall(MaxrEngine::Vector2Di position)
	{
		if (InRect(MaxrEngine::Vector2Di(), GetTileSize(), position))
		{
			tileType[position.x][position.y] = TileType::Wall;
		}
	}

	void LabyrinthBuilder::SetFloor(MaxrEngine::Vector2Di position)
	{
		if (InRect(MaxrEngine::Vector2Di(), GetTileSize(), position))
		{
			tileType[position.x][position.y] = TileType::Floor;
		}
	}

	MaxrEngine::Vector2Di LabyrinthBuilder::GetTileSize() const
	{
		if (tileType.size() > 0)
		{
			return MaxrEngine::Vector2Di(static_cast<int>(tileType.size()), static_cast<int>(tileType[0].size()));
		}
		else
		{
			return MaxrEngine::Vector2Di(0, 0);
		}
	}

	std::shared_ptr<Labyrinth> LabyrinthBuilder::ConstructLabyrinth()
	{
		auto settings = Settings::Instance();
		std::shared_ptr<Labyrinth> labyrinth = std::make_shared<Labyrinth>();
		auto labyrinthTransform = labyrinth->GetGameObject()->GetComponent<MaxrEngine::TransformComponent>();
		UpdateWallType();
		for (int i = 0; i < tileType.size(); ++i)
		{
			for (int j = 0; j < tileType[i].size(); ++j)
			{
				if (IsWall(MaxrEngine::Vector2Di(i, j)))
				{
					int textureId = 0;
					switch (tileType[i][j])
					{
					case TileType::HorizontalWall:
						textureId = 36;
						break;
					case TileType::VerticalWall:
						textureId = 4;
						break;
					default:
						break;
					}
					auto wall = std::make_shared<Wall>(labyrinthTransform->GetWorldPosition(), textureId, MaxrEngine::Vector2Di(settings->mapTileSize, settings->mapTileSize));
					auto wallTransform = wall->GetGameObject()->GetComponent<MaxrEngine::TransformComponent>();
					wallTransform->SetParent(labyrinthTransform);
					wallTransform->SetLocalPosition(GetTylePosition({ i,j }));
					labyrinth->walls.emplace_back(wall);
				}
				else
				{
					if (tileType[i][j] == TileType::Floor)
					{
						int textureId = usableFloorTextureId[rand() % usableFloorTextureId.size()];
						auto floor = std::make_shared<Floor>(labyrinthTransform->GetWorldPosition(), textureId, MaxrEngine::Vector2Di(settings->mapTileSize, settings->mapTileSize));
						auto floorTransform = floor->GetGameObject()->GetComponent<MaxrEngine::TransformComponent>();
						floorTransform->SetParent(labyrinthTransform);
						floorTransform->SetLocalPosition(GetTylePosition({ i,j }));
						labyrinth->floors.emplace_back(floor);
					}
				}
			}
		}
		return labyrinth;
	}

	void LabyrinthBuilder::UpdateWallType()
	{
		MaxrEngine::Vector2Di toLeft(-1, 0);
		MaxrEngine::Vector2Di toRight(1, 0);
		MaxrEngine::Vector2Di toUp(0, -1);
		MaxrEngine::Vector2Di toBottom(0, 1);
		for (int i = 0; i < tileType.size(); ++i)
		{
			for (int j = 0; j < tileType[i].size(); ++j)
			{
				MaxrEngine::Vector2Di currentPosition(i, j);
				if (IsWall(currentPosition))				
				{
					if (IsWall(currentPosition + toUp) || IsWall(currentPosition + toBottom))
					{
						tileType[i][j] = TileType::VerticalWall;
					}
					else
					{
						tileType[i][j] = TileType::HorizontalWall;
					}
				}
			}
		}
	}

	bool LabyrinthBuilder::IsWall(MaxrEngine::Vector2Di position)
	{
		if (InRect(MaxrEngine::Vector2Di(), GetTileSize(), position))
		{

			switch (tileType[position.x][position.y])
			{
			case TileType::Empty:
				return false;
				break;
			case TileType::Floor:
				return false;
				break;
			case TileType::Wall:
				return true;
				break;
			case TileType::HorizontalWall:
				return true;
				break;
			case TileType::VerticalWall:
				return true;
				break;
			default:
				return false;
				break;
			}
		}
		else
		{
			return false;
		}
	}
	MaxrEngine::Vector2Df LabyrinthBuilder::GetCenterInTyles()
	{
		return MaxrEngine::Convert<MaxrEngine::Vector2Df, MaxrEngine::Vector2Di>(GetTileSize()) * 0.5f;
	}

	MaxrEngine::Vector2Df LabyrinthBuilder::GetTylePosition(MaxrEngine::Vector2Di tilePosition)
	{
		auto settings = Settings::Instance();
		auto position = MaxrEngine::Convert<MaxrEngine::Vector2Df, MaxrEngine::Vector2Di>(tilePosition) - GetCenterInTyles();
		position *= static_cast<float>(settings->mapTileSize);
		return position;
	}
}