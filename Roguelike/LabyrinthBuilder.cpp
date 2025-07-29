#include "LabyrinthBuilder.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <map>
#include <memory>
#include <stack>
#include <utility>
#include <vector>

#include "Floor.h"
#include "Labyrinth.h"
#include "LabyrinthExit.h"
#include "Logger.h"
#include "Settings.h"
#include "TransformComponent.h"
#include "Utility.h"
#include "Vector.h"
#include "Wall.h"

namespace Roguelike {
enum class TileType {};

LabyrinthBuilder::LabyrinthBuilder() {
    usableFloorTextureId.push_back(0);
    usableFloorTextureId.push_back(1);
    usableFloorTextureId.push_back(2);
    usableFloorTextureId.push_back(8);
    usableFloorTextureId.push_back(10);
    exitCell = {-1, -1};
}

void LabyrinthBuilder::Generate(const BuildingParameters& parameters) {
    // Set random seed
    if (parameters.randSeed == -1) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    } else {
        std::srand(parameters.randSeed);
    }
    // filling tileGrid with desired size by walls
    StartBuilding({parameters.width, parameters.heigth}, TileType::Wall);
    // setting DFS start position in labyrinth interior
    if (parameters.startPosition.x < 0 || parameters.startPosition.y < 0) {
        // Get random position in Labyrinth interior
        startPosition = {1 + (std::rand() % (labyrinthTileWidth - 2)),
                         1 + (std::rand() % (labyrinthTileHeight - 2))};
    } else {
        // Set position by parameters
        startPosition = parameters.startPosition;
    }
    if (parameters.isAdjustingSizeAndStart) {
        AdjustStartPointAndSize();
    }
    // vector for marking visited locations
    std::vector<std::vector<bool>> visited;
    visited.resize(labyrinthTileWidth,
                   std::vector<bool>(labyrinthTileHeight, false));
    // stack for cells that will be processed
    std::stack<MaxrEngine::Vector2Di> cellStack;
    cellStack.push(startPosition);
    // Start DFS
    while (!cellStack.empty()) {
        // get cell for processing
        const auto currentCell = cellStack.top();
        cellStack.pop();
        // get availiable directions to move
        auto availiableDirections =
            GetAvaliableDirections(currentCell, visited);
        if (!availiableDirections.empty()) {
            cellStack.push(currentCell);
            // Select random available diretion
            const auto& selectedDirection =
                availiableDirections[std::rand() % availiableDirections.size()];
            // Add next cell
            const MaxrEngine::Vector2Di newCell =
                currentCell + selectedDirection;
            cellStack.push(newCell);
            // Make middle cell floor and surround it by walls
            const MaxrEngine::Vector2Di middleCell = {
                (newCell.x + currentCell.x) / 2,
                (newCell.y + currentCell.y) / 2};
            ProcessMiddleCell(middleCell, visited, selectedDirection);
        } else {
            /*Mark cell as dead end if it has no availiable direction on first
             * visit*/
            if (!visited[currentCell.x][currentCell.y]) {
                deadEnds.push_back(currentCell);
            }
        }
        /* Mark current cell as visited and place Floor in cellGrid*/
        visited[currentCell.x][currentCell.y] = true;
        tileGrid[currentCell.x][currentCell.y] = TileType::Floor;
    }
    FindAndEmplaceExit();
}

void LabyrinthBuilder::StartBuilding(const MaxrEngine::Vector2Di& newTileSize,
                                     const TileType fillTileType) {
    exitCell = {-1, -1};
    labyrinthTileWidth = newTileSize.x;
    labyrinthTileHeight = newTileSize.y;
    tileGrid = std::vector<std::vector<TileType>>(
        labyrinthTileWidth,
        std::vector<TileType>(labyrinthTileHeight, fillTileType));
}

void LabyrinthBuilder::AddRect(const RectFillingParameters& parameters) {
    // Clamping rect bottomLeft and size to labyrinth size
    const MaxrEngine::Vector2Di bottomLeft = {
        std::clamp(parameters.bottomLeft.x, 0, labyrinthTileWidth),
        std::clamp(parameters.bottomLeft.y, 0, labyrinthTileHeight)};
    const MaxrEngine::Vector2Di size = {
        std::clamp(parameters.size.x, 0, labyrinthTileWidth - bottomLeft.x),
        std::clamp(parameters.size.y, 0, labyrinthTileWidth - bottomLeft.y)};
    const MaxrEngine::Vector2Di topRight =
        bottomLeft + size - MaxrEngine::Vector2Di(1, 1);
    // Processing rect top and bottom border
    for (int i = bottomLeft.x; i <= topRight.x; ++i) {
        if (tileGrid[i][bottomLeft.y] != parameters.fillingTileType) {
            tileGrid[i][bottomLeft.y] = parameters.borderTileType;
        }
        if (tileGrid[i][topRight.y] != parameters.fillingTileType) {
            tileGrid[i][topRight.y] = parameters.borderTileType;
        }
    }
    // Processing rect left and right border
    for (int i = bottomLeft.y; i <= topRight.y; ++i) {
        if (tileGrid[bottomLeft.x][i] != parameters.fillingTileType) {
            tileGrid[bottomLeft.x][i] = parameters.borderTileType;
        }
        if (tileGrid[topRight.x][i] != parameters.fillingTileType) {
            tileGrid[topRight.x][i] = parameters.borderTileType;
        }
    }
    // Processing rect interior
    for (int i = bottomLeft.x + 1; i < topRight.x; ++i) {
        for (int j = bottomLeft.y + 1; j < topRight.y; ++j) {
            tileGrid[i][j] = parameters.fillingTileType;
        }
    }
}

void Roguelike::LabyrinthBuilder::AddFloorRect(MaxrEngine::Vector2Di bottomLeft,
                                               MaxrEngine::Vector2Di size) {
    AddRect(RectFillingParameters(bottomLeft, size, TileType::Wall,
                                  TileType::Floor));
}

void LabyrinthBuilder::SetWall(MaxrEngine::Vector2Di position) {
    if (InRect(MaxrEngine::Vector2Di(), GetTileSize(), position)) {
        tileGrid[position.x][position.y] = TileType::Wall;
    }
}

void LabyrinthBuilder::SetFloor(MaxrEngine::Vector2Di position) {
    if (InRect(MaxrEngine::Vector2Di(), GetTileSize(), position)) {
        tileGrid[position.x][position.y] = TileType::Floor;
    }
}

MaxrEngine::Vector2Di LabyrinthBuilder::GetTileSize() const {
    return MaxrEngine::Vector2Di(labyrinthTileWidth, labyrinthTileHeight);
}

void LabyrinthBuilder::SetExitCell(const MaxrEngine::Vector2Di& newExitCell) {
    if (InRect({0, 0}, {labyrinthTileWidth, labyrinthTileHeight},
               newExitCell)) {
        exitCell = newExitCell;
    } else {
        LOG_WARN("newExitCell must be in Labyrinth rect. Data not changed");
    }
}

const MaxrEngine::Vector2Di& LabyrinthBuilder::GetExitCell() const {
    return exitCell;
}

std::shared_ptr<Labyrinth> LabyrinthBuilder::ConstructLabyrinth() {
    auto* settings = Settings::Instance();
    // Create new Labyrinth object
    std::shared_ptr<Labyrinth> labyrinth =
        std::shared_ptr<Labyrinth>(new Labyrinth(
            MaxrEngine::Vector2Di(labyrinthTileWidth, labyrinthTileHeight)));
    // Store Generate results aside of TileTypes in Labyrinth
    labyrinth->startCell = startPosition;
    labyrinth->generationDeadEnd = deadEnds;
    auto* labyrinthTransform =
        labyrinth->GetGameObject()
            ->GetComponent<MaxrEngine::TransformComponent>();
    // TODO(MaxrRusich) : rework UpdateWallType to process more wall types in
    // different angles as corner wall, T-wall, etc. Change walls type according
    // to it surrounding
    UpdateWallType();
    // Going throw tileGrid and create Wall, Floor and Exit objects
    // Forming walkable tile grid in process
    for (int i = 0; i < tileGrid.size(); ++i) {
        for (int j = 0; j < tileGrid[i].size(); ++j) {
            if (IsWall(MaxrEngine::Vector2Di(i, j))) {
                // Wall cell case
                labyrinth->isTileWalkable[i][j] = false;
                int textureId = 0;
                switch (tileGrid[i][j]) {
                    case TileType::HorizontalWall:
                        textureId = 36;
                        break;
                    case TileType::VerticalWall:
                        textureId = 4;
                        break;
                    default:
                        break;
                }
                auto wall = std::make_shared<Wall>(
                    labyrinthTransform->GetWorldPosition(), textureId,
                    MaxrEngine::Vector2Di(settings->mapTileSize,
                                          settings->mapTileSize));
                auto* wallTransform =
                    wall->GetGameObject()
                        ->GetComponent<MaxrEngine::TransformComponent>();
                wallTransform->SetParent(labyrinthTransform);
                wallTransform->SetLocalPosition(GetTylePosition({i, j}));
                labyrinth->elements[i][j] = wall;
            } else if (tileGrid[i][j] == TileType::Floor) {
                // Floor cell case
                labyrinth->isTileWalkable[i][j] = true;
                const int textureId =
                    usableFloorTextureId[rand() % usableFloorTextureId.size()];
                auto floor = std::make_shared<Floor>(
                    labyrinthTransform->GetWorldPosition(), textureId,
                    MaxrEngine::Vector2Di(settings->mapTileSize,
                                          settings->mapTileSize));
                auto* floorTransform =
                    floor->GetGameObject()
                        ->GetComponent<MaxrEngine::TransformComponent>();
                floorTransform->SetParent(labyrinthTransform);
                floorTransform->SetLocalPosition(GetTylePosition({i, j}));
                labyrinth->elements[i][j] = floor;
            } else if (tileGrid[i][j] == TileType::Exit) {
                // Exit cell case
                labyrinth->isTileWalkable[i][j] = true;
                const int textureId = 16;
                auto exit = std::make_shared<LabyrinthExit>(
                    labyrinthTransform->GetWorldPosition(), textureId,
                    MaxrEngine::Vector2Di(settings->mapTileSize,
                                          settings->mapTileSize));
                auto* exitTransform =
                    exit->GetGameObject()
                        ->GetComponent<MaxrEngine::TransformComponent>();
                exitTransform->SetParent(labyrinthTransform);
                exitTransform->SetLocalPosition(GetTylePosition({i, j}));
                labyrinth->elements[i][j] = exit;
                labyrinth->exit = exit;
            }
        }
    }
    return labyrinth;
}

std::vector<MaxrEngine::Vector2Di> LabyrinthBuilder::GetAvaliableDirections(
    const MaxrEngine::Vector2Di& currentCell,
    const std::vector<std::vector<bool>>& visitiedCells) const {
    /*Defining possible directions: up, down, left, right (2 cells away to leave
     * space for walls).*/
    const std::vector<MaxrEngine::Vector2Di> directions{
        {0, -2},  // Up
        {2, 0},   // Right
        {0, 2},   // Down
        {-2, 0}   // Left
    };
    const MaxrEngine::Vector2Di interiorLabyrinthTopLeft = {1, 1};
    const MaxrEngine::Vector2Di interiorLabyrinthBottomRight = {
        labyrinthTileWidth - 2, labyrinthTileHeight - 2};
    std::vector<MaxrEngine::Vector2Di> availableDirections;
    // Checking all direction
    for (const auto& direction : directions) {
        auto possibleCell = currentCell + direction;
        /* Checking that possible cell are in labyrinth and was not visited
            before*/
        if (InRect(interiorLabyrinthTopLeft, interiorLabyrinthBottomRight,
                   possibleCell) &&
            !visitiedCells[possibleCell.x][possibleCell.y]) {
            availableDirections.push_back(direction);
        }
    }
    return availableDirections;
}

void LabyrinthBuilder::UpdateWallType() {
    const MaxrEngine::Vector2Di toLeft(-1, 0);
    const MaxrEngine::Vector2Di toRight(1, 0);
    const MaxrEngine::Vector2Di toUp(0, -1);
    const MaxrEngine::Vector2Di toBottom(0, 1);
    for (int i = 0; i < tileGrid.size(); ++i) {
        for (int j = 0; j < tileGrid[i].size(); ++j) {
            const MaxrEngine::Vector2Di currentPosition(i, j);
            if (IsWall(currentPosition)) {
                if (IsWall(currentPosition + toUp) ||
                    IsWall(currentPosition + toBottom)) {
                    tileGrid[i][j] = TileType::VerticalWall;
                } else {
                    tileGrid[i][j] = TileType::HorizontalWall;
                }
            }
        }
    }
}

bool LabyrinthBuilder::IsWall(MaxrEngine::Vector2Di position) const {
    if (InRect(MaxrEngine::Vector2Di(), GetTileSize(), position)) {
        switch (tileGrid[position.x][position.y]) {
            case TileType::Wall:
                return true;
                break;
            case TileType::HorizontalWall:
                return true;
                break;
            case TileType::VerticalWall:
                return true;
                break;
            case TileType::Empty:
                return false;
                break;
            case TileType::Floor:
                return false;
                break;
            default:
                return false;
                break;
        }
    } else {
        return false;
    }
}

void Roguelike::LabyrinthBuilder::AdjustStartPointAndSize() {
    // Adding 1 to startPosition x and y, labirinth width and height if it is
    // even
    labyrinthTileWidth += labyrinthTileWidth % 2 == 0 ? 1 : 0;
    labyrinthTileHeight += labyrinthTileHeight % 2 == 0 ? 1 : 0;
    startPosition.x += startPosition.x % 2 == 0 ? 1 : 0;
    startPosition.y += startPosition.y % 2 == 0 ? 1 : 0;
}

void LabyrinthBuilder::ProcessMiddleCell(
    const MaxrEngine::Vector2Di& middleCell,
    std::vector<std::vector<bool>>& visited,
    const MaxrEngine::Vector2Di& selectedDirection) {
    visited[middleCell.x][middleCell.y] = true;
    tileGrid[middleCell.x][middleCell.y] = TileType::Floor;
    // Check that moving direction vas horizontal or vertical
    if (selectedDirection.y == 0) {
        // Horizontal direction
        // Work with cell below middle
        if (middleCell.y - 1 > 0) {
            visited[middleCell.x][middleCell.y - 1] = true;
            tileGrid[middleCell.x][middleCell.y - 1] = TileType::Wall;
        }
        // Work with cell above middle
        if (middleCell.y + 1 < labyrinthTileHeight) {
            visited[middleCell.x][middleCell.y + 1] = true;
            tileGrid[middleCell.x][middleCell.y + 1] = TileType::Wall;
        }
    } else {
        // Vertical direction
        // Work with cell to ther left middle
        if (middleCell.x - 1 > 0) {
            visited[middleCell.x - 1][middleCell.y] = true;
            tileGrid[middleCell.x - 1][middleCell.y] = TileType::Wall;
        }
        // Work with cell to the right from middle
        if (middleCell.x + 1 < labyrinthTileHeight) {
            visited[middleCell.x + 1][middleCell.y] = true;
            tileGrid[middleCell.x + 1][middleCell.y] = TileType::Wall;
        }
    }
}

void LabyrinthBuilder::FindAndEmplaceExit() {
    // set for deadEnds near the edge, sorted by distancs to startPoint
    std::multimap<float, MaxrEngine::Vector2Di> deadEndsNearEdge;
    for (const auto& deadEnd : deadEnds) {
        if (deadEnd.x == 1 || deadEnd.x == labyrinthTileWidth - 2 ||
            deadEnd.y == 1 || deadEnd.y == labyrinthTileHeight - 2) {
            deadEndsNearEdge.insert(std::pair<float, MaxrEngine::Vector2Di>(
                (Convert<MaxrEngine::Vector2Df>(deadEnd - startPosition))
                    .GetLength(),
                deadEnd));
        }
    }
    // Try to get most distanced deadEnd
    auto cellNearExit = deadEndsNearEdge.crbegin();
    if (cellNearExit != deadEndsNearEdge.crend()) {
        // if such deadEnd founded, calculating exitCell on edge of Labyrinth
        auto exitCell = cellNearExit->second;
        if (exitCell.x == 1) {
            exitCell.x = 0;
        } else if (exitCell.x == labyrinthTileWidth - 2) {
            exitCell.x = labyrinthTileWidth - 1;
        } else if (exitCell.y == 1) {
            exitCell.y = 0;
        } else if (exitCell.y == labyrinthTileHeight - 2) {
            exitCell.y = labyrinthTileHeight - 1;
        }
        tileGrid[exitCell.x][exitCell.y] = TileType::Exit;
    } else {
        RandomlyEmplaceExit();
    }
}

void LabyrinthBuilder::RandomlyEmplaceExit() {
    const MaxrEngine::Vector2Di zeroVector = {0, 0};
    MaxrEngine::Vector2Di exitCell = zeroVector;
    while (exitCell == zeroVector) {
        // Choosing random coordinates for exitCell
        const int xCoordinate = 1 + (std::rand() % (labyrinthTileWidth - 1));
        const int yCoordinate = 1 + (std::rand() % (labyrinthTileHeight - 1));
        // Chosing random edge where to place exitCell
        enum Edge { Up, Right, Down, Left };
        const Edge randomEdge = static_cast<Edge>(std::rand() % 4);
        switch (randomEdge) {
            case Up:
                if (tileGrid[xCoordinate][1] == TileType::Floor) {
                    exitCell = {xCoordinate, 0};
                }
                break;
            case Down:
                if (tileGrid[xCoordinate][labyrinthTileHeight - 2] ==
                    TileType::Floor) {
                    exitCell = {xCoordinate, labyrinthTileHeight - 1};
                }
                break;
            case Left:
                if (tileGrid[1][yCoordinate] == TileType::Floor) {
                    exitCell = {0, yCoordinate};
                }
                break;
            case Right:
                if (tileGrid[labyrinthTileWidth - 2][yCoordinate] ==
                    TileType::Floor) {
                    exitCell = {labyrinthTileWidth - 1, yCoordinate};
                }
                break;
        }
    }
    tileGrid[exitCell.x][exitCell.y] = TileType::Exit;
}

MaxrEngine::Vector2Df LabyrinthBuilder::GetCenterInTyles() const {
    const MaxrEngine::Vector2Df oneVector(1.0F, 1.0F);
    return Half(
        (MaxrEngine::Convert<MaxrEngine::Vector2Df, MaxrEngine::Vector2Di>(
             GetTileSize()) -
         oneVector));
}

MaxrEngine::Vector2Df LabyrinthBuilder::GetTylePosition(
    MaxrEngine::Vector2Di tilePosition) {
    auto* settings = Settings::Instance();
    auto position =
        MaxrEngine::Convert<MaxrEngine::Vector2Df, MaxrEngine::Vector2Di>(
            tilePosition) -
        GetCenterInTyles();
    position *= static_cast<float>(settings->mapTileSize);
    return position;
}
}  // namespace Roguelike