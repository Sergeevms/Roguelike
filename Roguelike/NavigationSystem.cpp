#include "NavigationSystem.h"

#include <algorithm>
#include <memory>
#include <vector>

#include "Labyrinth.h"
#include "Settings.h"
#include "Utility.h"
#include "Vector.h"

namespace Roguelike {
using Vector2Df = MaxrEngine::Vector2Df;
using Vector2Di = MaxrEngine::Vector2Di;
std::shared_ptr<NavigationSystem> NavigationSystem::Instance() {
    const static std::shared_ptr<NavigationSystem> instance =
        std::shared_ptr<NavigationSystem>(new NavigationSystem,
                                          [](NavigationSystem*) {});
    return instance;
};
void NavigationSystem::SetUpMap(const Labyrinth& labyrinth) {
    nodes.clear();
    edges.clear();
    auto walkable = labyrinth.GetIsTileWalkable();
    const Vector2Di labyrinthSize = {static_cast<int>(walkable.size()),
                                     static_cast<int>(walkable[0].size())};
    // Check fi tile in labyrinth and walkable
    auto tileWalkable = [&labyrinthSize, &walkable](const Vector2Di& cell) {
        if (!(InRange(cell.x, 0, labyrinthSize.x - 1) &&
              InRange(cell.y, 0, labyrinthSize.y - 1))) {
            return false;
        }
        return walkable[cell.x][cell.y].operator bool();
    };
    constexpr int directionCount = 4;
    enum Direction { Left, Up, Right, Down };
    // Converts int to Direction
    auto direction = [](const int possibleDirection) {
        return static_cast<Direction>((directionCount + possibleDirection) %
                                      directionCount);
    };
    auto turnRight = [&direction](const Direction currentDirection) {
        return direction(currentDirection + 1);
    };
    auto turnLeft = [&direction](const Direction currentDirection) {
        return direction(currentDirection - 1);
    };
    const std::vector<Vector2Di> directionVector = {
        {-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    // Check that tile don't have walkable neighbors
    auto tileBlocked = [&tileWalkable,
                        &directionVector](const Vector2Di& cell) {
        for (int i = 0; i < directionCount; i++) {
            if (tileWalkable(cell + directionVector[i])) {
                return false;
            }
        }
        return true;
    };

    std::vector<Vector2Di> untochedWalls;

    for (auto x = 0; x < labyrinthSize.x; ++x) {
        for (auto y = 0; y < labyrinthSize.y; ++y) {
            if (!tileWalkable({x, y})) {
                if (!tileBlocked({x, y})) {
                    untochedWalls.push_back({x, y});
                }
            }
        }
    }
    const float offset =
        static_cast<float>(Settings::Instance()->mapTileSize) / 3.0F;

    const std::vector<Vector2Df> rightTurnOffset = {{offset, -offset},
                                                    {offset, offset},
                                                    {-offset, offset},
                                                    {-offset, -offset}};
    const std::vector<Vector2Df> leftTurnOffset = {{-offset, -offset},
                                                   {offset, -offset},
                                                   {offset, offset},
                                                   {-offset, offset}};

    while (!untochedWalls.empty()) {
        const int firstNode = static_cast<int>(nodes.size());
        const int firstEdge = static_cast<int>(edges.size());
        auto& blocked = *untochedWalls.begin();
        std::vector<Vector2Di> touchedWalls;
        Vector2Di startCell;
        Direction currentDirection;
        for (int i = 0; i < directionCount; ++i) {
            startCell = blocked + directionVector[i];
            if (tileWalkable(startCell)) {
                nodes.push_back(std::make_unique<Node>(
                    labyrinth.GetCellCoordinates(startCell) -
                    leftTurnOffset[direction(i)]));
                currentDirection = turnRight(direction(i));
                break;
            }
        }
        Vector2Di currentCell = startCell;
        auto addNode = [this](const Vector2Df& newNode) {
            auto* prevNode = nodes.back().get();
            nodes.push_back(std::make_unique<Node>(newNode));
            edges.push_back({prevNode, nodes.back().get()});
        };
        auto onLine = [](const Vector2Df& checkNodeCoord,
                         const Vector2Df& startNodeCoord,
                         const Vector2Df& endNodeCoord) {
            return (checkNodeCoord.x == startNodeCoord.x &&
                    InRange(checkNodeCoord.y,
                            std::min(startNodeCoord.y, endNodeCoord.y),
                            std::max(startNodeCoord.y, endNodeCoord.y))) ||
                   (checkNodeCoord.y == startNodeCoord.y &&
                    InRange(checkNodeCoord.x,
                            std::min(startNodeCoord.x, endNodeCoord.x),
                            std::max(startNodeCoord.x, endNodeCoord.x)));
        };

        while (static_cast<int>(edges.size()) - firstEdge < 3 ||
               !onLine(nodes[firstNode]->coordinates,
                       edges.back().first->coordinates,
                       edges.back().second->coordinates)) {
            Vector2Di newCell;
            int turns = -1;
            Direction newDirection;
            for (newDirection = turnRight(currentDirection);
                 turns < directionCount;
                 newDirection = turnLeft(newDirection), ++turns) {
                newCell = currentCell + directionVector[newDirection];
                if (tileWalkable(newCell)) {
                    break;
                }
            }
            if (turns < 0) {
                addNode(labyrinth.GetCellCoordinates(currentCell) +
                        rightTurnOffset[currentDirection]);
            } else {
                touchedWalls.push_back(
                    currentCell + directionVector[turnRight(currentDirection)]);
                for (int i = 1; i <= turns; ++i) {
                    addNode(labyrinth.GetCellCoordinates(currentCell) +
                            leftTurnOffset[currentDirection]);
                    currentDirection = turnLeft(currentDirection);
                    touchedWalls.push_back(
                        currentCell +
                        directionVector[turnRight(currentDirection)]);
                }
            }
            currentCell = newCell;
            currentDirection = newDirection;
        }
        // Remove first added edge and node if it isn't on obstacle corner
        if (nodes[firstNode]->coordinates != nodes.back()->coordinates) {
            nodes.erase(nodes.begin() + firstNode);
            edges.erase(edges.begin() + firstEdge);
        }
        nodes.pop_back();
        edges.back().second = nodes[firstNode].get();
        for (auto touchedWall : touchedWalls) {
            untochedWalls.erase(
                std::remove_if(untochedWalls.begin(), untochedWalls.end(),
                               [&touchedWall](const Vector2Di& cell) {
                                   return cell == touchedWall;
                               }),
                untochedWalls.end());
        }
    }
    auto lineClear = [this, &labyrinth, &tileWalkable](const Node* firstNode,
                                                       const Node* secondNode) {
        auto middleCell = labyrinth.GetGridCoordinates(
            (firstNode->coordinates + secondNode->coordinates) * 0.5F);
        if (!tileWalkable(middleCell)) {
            return false;
        }
        const auto line = secondNode->coordinates - firstNode->coordinates;
        for (auto edge : edges) {
            if (firstNode == edge.first || firstNode == edge.second ||
                secondNode == edge.first || secondNode == edge.second) {
                continue;
            }
            float firstSign = MaxrEngine::CrossProduct(
                line, edge.first->coordinates - firstNode->coordinates);
            float secondSign = MaxrEngine::CrossProduct(
                line, edge.second->coordinates - firstNode->coordinates);

            if (firstSign * secondSign > 0.F ||
                (firstSign == 0.0F && secondSign == 0.0F)) {
                continue;
            }

            const auto edgeLine =
                edge.second->coordinates - edge.first->coordinates;
            firstSign = MaxrEngine::CrossProduct(
                edgeLine, firstNode->coordinates - edge.first->coordinates);
            secondSign = MaxrEngine::CrossProduct(
                edgeLine, secondNode->coordinates - edge.first->coordinates);
            if (firstSign * secondSign > 0.F ||
                (firstSign == 0.0F && secondSign == 0.0F)) {
                continue;
            }
            return false;
        }
        return true;
    };
    for (int i = 0; i < nodes.size(); ++i) {
        for (int j = i + 1; j < nodes.size(); ++j) {
            if (lineClear(nodes[i].get(), nodes[j].get())) {
                nodes[i]->visibleNodes.push_back(nodes[j].get());
                nodes[j]->visibleNodes.push_back(nodes[i].get());
            }
        }
    }
}
std::vector<Vector2Df> NavigationSystem::GetPath(const Vector2Df& begin,
                                                 const Vector2Df& end) {
    return std::vector<Vector2Df>();
}
}  // namespace Roguelike