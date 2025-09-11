#include "NavigationSystem.h"

#include <algorithm>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "DefaultActorsSettings.h"
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

void Roguelike::NavigationSystem::SetUpMap(
    std::shared_ptr<const Labyrinth> newLabyrinth) {
    nodes.clear();
    borders.clear();
    labyrinthPtr = newLabyrinth;
    auto labyrinth = newLabyrinth;

    // Support functions and consts
    constexpr int directionCount = 4;
    enum Direction { Left, Up, Right, Down };
    // Converts int to Direction, looped by direction count
    auto direction = [](const int possibleDirection) {
        return static_cast<Direction>((directionCount + possibleDirection) %
                                      directionCount);
    };
    // Returns direction to right from current
    auto turnRight = [&direction](const Direction currentDirection) {
        return direction(currentDirection + 1);
    };
    // Returns direction to left from current
    auto turnLeft = [&direction](const Direction currentDirection) {
        return direction(currentDirection - 1);
    };
    // Vector to add according to direction casted to int to get next cell on
    // that direction
    const std::vector<Vector2Di> directionVector = {
        {-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    // Check that tile don't have walkable neighbors
    auto tileBlocked = [&labyrinth, &directionVector](const Vector2Di& cell) {
        for (int i = 0; i < directionCount; i++) {
            if (labyrinth->IsTileWalkable(cell + directionVector[i])) {
                return false;
            }
        }
        return true;
    };
    // Vector to store unwalkable tiles that can be touched but not yet
    std::vector<Vector2Di> untochedWalls;
    const auto& labyrinthTileSize = labyrinth->GetTileSize();
    for (auto x = 0; x < labyrinthTileSize.x; ++x) {
        for (auto y = 0; y < labyrinthTileSize.y; ++y) {
            if (!labyrinth->IsTileWalkable({x, y})) {
                if (!tileBlocked({x, y})) {
                    untochedWalls.push_back({x, y});
                }
            }
        }
    }

    const float offset =
        Half(static_cast<float>(Settings::Instance()->mapTileSize) -
             DefaultSettings::defaultActorSpriteSize);
    // offset used to place Node on rigth turn in algo
    const std::vector<Vector2Df> rightTurnOffset = {{offset, -offset},
                                                    {offset, offset},
                                                    {-offset, offset},
                                                    {-offset, -offset}};
    // offset used to place Node on left turn in algo
    const std::vector<Vector2Df> leftTurnOffset = {{-offset, -offset},
                                                   {offset, -offset},
                                                   {offset, offset},
                                                   {-offset, offset}};

    while (!untochedWalls.empty()) {
        const int firstNode = static_cast<int>(nodes.size());
        const int firstEdge = static_cast<int>(borders.size());
        auto& blocked = *untochedWalls.begin();
        std::vector<Vector2Di> touchedWalls;
        Vector2Di startCell;
        Direction currentDirection;
        for (int i = 0; i < directionCount; ++i) {
            startCell = blocked + directionVector[i];
            if (labyrinth->IsTileWalkable(startCell)) {
                nodes.push_back(std::make_unique<Node>(
                    labyrinth->GetCellCoordinates(startCell) -
                    leftTurnOffset[direction(i)]));
                currentDirection = turnRight(direction(i));
                break;
            }
        }
        Vector2Di currentCell = startCell;
        auto addNode = [this](const Vector2Df& newNode) {
            auto* prevNode = nodes.back().get();
            nodes.push_back(std::make_unique<Node>(newNode));
            borders.push_back({prevNode, nodes.back().get()});
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

        while (static_cast<int>(borders.size()) - firstEdge < 3 ||
               !onLine(nodes[firstNode]->coordinates,
                       borders.back().first->coordinates,
                       borders.back().second->coordinates)) {
            Vector2Di newCell;
            int turns = -1;
            Direction newDirection;
            for (newDirection = turnRight(currentDirection);
                 turns < directionCount;
                 newDirection = turnLeft(newDirection), ++turns) {
                newCell = currentCell + directionVector[newDirection];
                if (labyrinth->IsTileWalkable(newCell)) {
                    break;
                }
            }
            if (turns < 0) {
                addNode(labyrinth->GetCellCoordinates(currentCell) +
                        rightTurnOffset[currentDirection]);
            } else {
                touchedWalls.push_back(
                    currentCell + directionVector[turnRight(currentDirection)]);
                for (int i = 1; i <= turns; ++i) {
                    addNode(labyrinth->GetCellCoordinates(currentCell) +
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
            borders.erase(borders.begin() + firstEdge);
        }
        nodes.pop_back();
        borders.back().second = nodes[firstNode].get();
        for (auto& touchedWall : touchedWalls) {
            untochedWalls.erase(
                std::remove_if(untochedWalls.begin(), untochedWalls.end(),
                               [&touchedWall](const Vector2Di& cell) {
                                   return cell == touchedWall;
                               }),
                untochedWalls.end());
        }
    }

    AddEdges();

    Emit();
}
std::vector<Vector2Df> NavigationSystem::GetPath(const Vector2Df& begin,
                                                 const Vector2Df& end) {
    auto start = std::make_unique<Node>(begin);
    auto finish = std::make_unique<Node>(end);

    // Check that we can go strait to finish
    if (IsNotCrossingBorders(start.get(), finish.get())) {
        return {end};
    }
    using NodeWithWeight = std::pair<Node*, float>;
    auto queueComporator = [](const NodeWithWeight& firstNode,
                              const NodeWithWeight& secondNode) {
        return secondNode.second > firstNode.second;
    };
    std::priority_queue<NodeWithWeight, std::vector<NodeWithWeight>,
                        decltype(queueComporator)>
        nodesQueue(queueComporator);
    nodesQueue.push(NodeWithWeight(start.get(), 0.0F));

    // Addition weight for A* (distance from node to finish)
    std::unordered_map<Node*, float> additionalCosts;
    // Current path to node weight
    std::unordered_map<Node*, float> currentWeights;
    // Node where from we came - to restore path
    std::unordered_map<Node*, Node*> cameFrom;
    // Modified nodes
    std::unordered_set<Node*> nodesToClear;

    for (auto& node : nodes) {
        // Try to add edge from start
        if (IsNotCrossingBorders(start.get(), node.get())) {
            const float distance =
                (start->coordinates - node->coordinates).GetLength();
            start->edges.push_back(Edge(node.get(), distance));
        }
        // Adding edges to finish
        if (IsNotCrossingBorders(node.get(), finish.get())) {
            const float distance =
                (finish->coordinates - node->coordinates).GetLength();
            additionalCosts[node.get()] = distance;
            node->edges.push_back(Edge(finish.get(), distance));
            nodesToClear.insert(node.get());
        }
    }

    // Start A*
    while (!nodesQueue.empty()) {
        const NodeWithWeight currentNode = nodesQueue.top();
        if (currentNode.first == finish.get()) {
            break;
        }
        nodesQueue.pop();
        for (auto& edge : currentNode.first->edges) {
            const float newWeight =
                edge.distance + currentWeights[currentNode.first];
            auto currentWeight = currentWeights.find(edge.node);
            if (currentWeight == currentWeights.end() ||
                currentWeight->second > newWeight) {
                currentWeights[edge.node] = newWeight;
                auto priorityWeight = newWeight + additionalCosts[edge.node];
                nodesQueue.push(NodeWithWeight(edge.node, priorityWeight));
                cameFrom[edge.node] = currentNode.first;
            }
        }
    }
    // Remove edges to finish from precalculated graph
    for (const auto& node : nodesToClear) {
        node->edges.pop_back();
    }
    std::vector<Vector2Df> path;
    Node* currentNode = finish.get();
    if (cameFrom[currentNode] == nullptr) {
        return path;
    }
    while (cameFrom[currentNode] != start.get()) {
        path.push_back(currentNode->coordinates);
        currentNode = cameFrom[currentNode];
    }
    std::reverse(path.begin(), path.end());
    return path;
}
bool NavigationSystem::IsNotCrossingBorders(const Node* firstNode,
                                            const Node* secondNode) {
    constexpr float half = 0.5F;
    if (auto labirnth = labyrinthPtr.lock()) {
        auto middleCell = labirnth->GetGridCoordinates(
            (firstNode->coordinates + secondNode->coordinates) * half);
        if (!labirnth->IsTileWalkable(middleCell)) {
            return false;
        }
        const auto line = secondNode->coordinates - firstNode->coordinates;
        for (auto edge : borders) {
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
    }
    return false;
}
void NavigationSystem::AddEdges() {
    for (int i = 0; i < nodes.size(); ++i) {
        for (int j = i + 1; j < nodes.size(); ++j) {
            if (IsNotCrossingBorders(nodes[i].get(), nodes[j].get())) {
                const float distance =
                    (nodes[i]->coordinates - nodes[j]->coordinates).GetLength();
                nodes[i]->edges.push_back(Edge(nodes[j].get(), distance));
                nodes[j]->edges.push_back(Edge(nodes[i].get(), distance));
            }
        }
    }
}
}  // namespace Roguelike