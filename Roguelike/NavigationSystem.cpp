#include "NavigationSystem.h"

#include <algorithm>
#include <array>
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

const std::array<Vector2Di, NavigationSystem::Direction::directionsCount>
    NavigationSystem::Direction::directionVector = {
        Vector2Di(-1, 0), Vector2Di(0, -1), Vector2Di(1, 0), Vector2Di(0, 1)};
std::array<Vector2Df, NavigationSystem::Direction::directionsCount>
    NavigationSystem::Direction::leftTurnOffset = {
        Vector2Df(0.0F, 0.0F), Vector2Df(0.0F, 0.0F), Vector2Df(0.0F, 0.0F),
        Vector2Df(0.0F, 0.0F)};
std::array<Vector2Df, NavigationSystem::Direction::directionsCount>
    NavigationSystem::Direction::rightTurnOffset = {
        Vector2Df(0.0F, 0.0F), Vector2Df(0.0F, 0.0F), Vector2Df(0.0F, 0.0F),
        Vector2Df(0.0F, 0.0F)};

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

    // Vector to store unwalkable tiles that can be touched but not yet
    std::vector<Vector2Di> untochedCells = GetCellsToProcess();

    Direction::SetOffset(
        Half(static_cast<float>(Settings::Instance()->mapTileSize) -
             DefaultSettings::defaultActorSpriteSize));

    while (!untochedCells.empty()) {
        ProcessArea(untochedCells);
    }

    CreateEdges();

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
std::vector<MaxrEngine::Vector2Di> NavigationSystem::GetCellsToProcess() const {
    std::vector<MaxrEngine::Vector2Di> untochedCells;
    // Check that tile don't have walkable neighbors
    if (auto labyrinth = labyrinthPtr.lock()) {
        auto tileBlocked = [&labyrinth](const Vector2Di& cell) {
            return std::all_of(
                Direction::directionVector.begin(),
                Direction::directionVector.end(),
                [&cell, &labyrinth](const Vector2Di& direction) {
                    return !labyrinth->IsTileWalkable(cell + direction);
                });
        };
        const auto& labyrinthTileSize = labyrinth->GetTileSize();
        for (auto x = 0; x < labyrinthTileSize.x; ++x) {
            for (auto y = 0; y < labyrinthTileSize.y; ++y) {
                if (!labyrinth->IsTileWalkable({x, y})) {
                    if (!tileBlocked({x, y})) {
                        untochedCells.push_back({x, y});
                    }
                }
            }
        }
    }
    return untochedCells;
}
void NavigationSystem::ProcessArea(
    std::vector<MaxrEngine::Vector2Di>& untouchedCells) {
    auto labyrinth = labyrinthPtr.lock();
    const int firstNode = static_cast<int>(nodes.size());
    const int firstEdge = static_cast<int>(borders.size());
    auto& startUnwalkableCell = *untouchedCells.begin();
    std::vector<Vector2Di> touchedWalls;
    Direction currentDirection;
    // Find start cell
    while (!labyrinth->IsTileWalkable(startUnwalkableCell +
                                      currentDirection.DirectionVector())) {
        currentDirection.TurnRight();
    }
    Vector2Di currentCell =
        startUnwalkableCell + currentDirection.DirectionVector();
    nodes.push_back(
        std::make_unique<Node>(labyrinth->GetCellCoordinates(currentCell) -
                               currentDirection.LeftTurnOffset()));
    currentDirection.TurnRight();

    auto addNode = [this](const Vector2Df& newNode) {
        auto* prevNode = nodes.back().get();
        nodes.push_back(std::make_unique<Node>(newNode));
        borders.push_back({prevNode, nodes.back().get()});
    };

    if (std::all_of(Direction::directionVector.begin(),
                    Direction::directionVector.end(),
                    [&currentCell, &labyrinth](const Vector2Di& direction) {
                        return !labyrinth->IsTileWalkable(currentCell +
                                                          direction);
                    })) {
        for (int i = 0; i < Direction::directionsCount; ++i) {
            addNode(labyrinth->GetCellCoordinates(currentCell) +
                    currentDirection.LeftTurnOffset());
            touchedWalls.push_back(currentCell +
                                   currentDirection.DirectionVector());
            currentDirection.TurnLeft();
        }
    }

    while (static_cast<int>(borders.size()) - firstEdge < 3 ||
           !OnSegment(nodes[firstNode]->coordinates,
                      borders.back().first->coordinates,
                      borders.back().second->coordinates)) {
        Direction newDirection = Direction::TurnRight(currentDirection);
        while (!labyrinth->IsTileWalkable(currentCell +
                                          newDirection.DirectionVector())) {
            newDirection.TurnLeft();
        }
        if (newDirection == Direction::TurnRight(currentDirection)) {
            addNode(labyrinth->GetCellCoordinates(currentCell) +
                    currentDirection.RightTurnOffset());
            currentDirection.TurnRight();
        } else {
            touchedWalls.push_back(
                currentCell +
                Direction::TurnRight(currentDirection).DirectionVector());
            while (currentDirection != newDirection) {
                addNode(labyrinth->GetCellCoordinates(currentCell) +
                        currentDirection.LeftTurnOffset());
                touchedWalls.push_back(currentCell +
                                       currentDirection.DirectionVector());
                currentDirection.TurnLeft();
            }
        }
        currentCell += currentDirection.DirectionVector();
    }
    // Remove first added edge and node if it isn't on obstacle corner
    if (nodes[firstNode]->coordinates != nodes.back()->coordinates) {
        nodes.erase(nodes.begin() + firstNode);
        borders.erase(borders.begin() + firstEdge);
    }
    nodes.pop_back();
    borders.back().second = nodes[firstNode].get();
    for (auto& touchedWall : touchedWalls) {
        untouchedCells.erase(
            std::remove_if(untouchedCells.begin(), untouchedCells.end(),
                           [&touchedWall](const Vector2Di& cell) {
                               return cell == touchedWall;
                           }),
            untouchedCells.end());
    }
}
void NavigationSystem::CreateEdges() {
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

NavigationSystem::Direction::Direction(const Name direction)
    : value(direction) {}
NavigationSystem::Direction::Direction(const int direction) {
    value = static_cast<Name>(direction % directionsCount);
}

int NavigationSystem::Direction::ToInt() const {
    return static_cast<int>(value);
}
int NavigationSystem::Direction::ToInt(Name direction) {
    return static_cast<int>(direction);
}

void NavigationSystem::Direction::TurnLeft() {
    value =
        static_cast<Name>((ToInt() - 1 + directionsCount) % directionsCount);
}
NavigationSystem::Direction NavigationSystem::Direction::TurnLeft(
    const Direction direction) {
    return TurnLeft(direction.value);
}
NavigationSystem::Direction NavigationSystem::Direction::TurnLeft(
    const Name direction) {
    return TurnLeft(ToInt(direction));
}
NavigationSystem::Direction NavigationSystem::Direction::TurnLeft(
    const int direction) {
    return Direction(direction - 1 + directionsCount);
}

void NavigationSystem::Direction::TurnRight() {
    value = static_cast<Name>((ToInt() + 1) % directionsCount);
}
NavigationSystem::Direction NavigationSystem::Direction::TurnRight(
    const Direction direction) {
    return TurnRight(direction.value);
}
NavigationSystem::Direction NavigationSystem::Direction::TurnRight(
    const Name direction) {
    return TurnRight(ToInt(direction));
}
NavigationSystem::Direction NavigationSystem::Direction::TurnRight(
    const int direction) {
    return Direction(direction + 1);
}
const MaxrEngine::Vector2Di& NavigationSystem::Direction::DirectionVector()
    const {
    return directionVector[ToInt()];
}
const MaxrEngine::Vector2Di& NavigationSystem::Direction::DirectionVector(
    Name direction) {
    return directionVector[static_cast<int>(direction)];
}
const MaxrEngine::Vector2Di& NavigationSystem::Direction::DirectionVector(
    const int direction) {
    return Direction(direction).DirectionVector();
}
void NavigationSystem::Direction::SetOffset(const float offset) {
    rightTurnOffset = {Vector2Df(offset, -offset), Vector2Df(offset, offset),
                       Vector2Df(-offset, offset), Vector2Df(-offset, -offset)};
    leftTurnOffset = {Vector2Df(-offset, -offset), Vector2Df(offset, -offset),
                      Vector2Df(offset, offset), Vector2Df(-offset, offset)};
}
const MaxrEngine::Vector2Df& NavigationSystem::Direction::LeftTurnOffset()
    const {
    return leftTurnOffset[ToInt()];
}
const MaxrEngine::Vector2Df& NavigationSystem::Direction::LeftTurnOffset(
    const Name direction) {
    return leftTurnOffset[ToInt(direction)];
}
const MaxrEngine::Vector2Df& NavigationSystem::Direction::LeftTurnOffset(
    const int direction) {
    return Direction(direction).LeftTurnOffset();
}
const MaxrEngine::Vector2Df& NavigationSystem::Direction::RightTurnOffset()
    const {
    return rightTurnOffset[ToInt()];
}
const MaxrEngine::Vector2Df& NavigationSystem::Direction::RightTurnOffset(
    const Name direction) {
    return rightTurnOffset[ToInt(direction)];
}
const MaxrEngine::Vector2Df& NavigationSystem::Direction::RightTurnOffset(
    const int direction) {
    return Direction(direction).RightTurnOffset();
}
}  // namespace Roguelike