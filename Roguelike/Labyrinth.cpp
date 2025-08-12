#include "Labyrinth.h"

#include <memory>
#include <vector>

#include "Floor.h"
#include "GameObjectContainer.h"
#include "LabyrinthElement.h"
#include "LabyrinthExit.h"
#include "Rect.h"
#include "TransformComponent.h"
#include "Vector.h"
#include "Wall.h"

namespace Roguelike {
const MaxrEngine::FloatRect Labyrinth::GetLabyrinthCoodinatesRect() {
    return MaxrEngine::FloatRect(GetCellCoordinates({0, 0}),
                                 GetCellCoordinates({size.x - 1, size.y - 1}));
}

Labyrinth::Labyrinth(const MaxrEngine::Vector2Di& size)
    : GameObjectContainer("Labyrinth") {
    Labyrinth::size = size;
    isTileWalkable.resize(size.x, std::vector<bool>(size.y, false));
    elements.resize(size.x, std::vector<std::shared_ptr<LabyrinthElement>>(
                                size.y, nullptr));
}

std::vector<std::weak_ptr<Wall>> Roguelike::Labyrinth::GetWalls() const {
    std::vector<std::weak_ptr<Wall>> walls;
    for (const auto& elementsColumn : elements) {
        for (const auto& element : elementsColumn) {
            if (auto wall = std::dynamic_pointer_cast<Wall>(element)) {
                walls.push_back(wall);
            }
        }
    }
    return walls;
}

std::vector<std::weak_ptr<Floor>> Labyrinth::GetFloors() const {
    std::vector<std::weak_ptr<Floor>> floors;
    for (const auto& elementsColumn : elements) {
        for (const auto& element : elementsColumn) {
            if (auto floor = std::dynamic_pointer_cast<Floor>(element)) {
                floors.push_back(floor);
            }
        }
    }
    return floors;
}

std::shared_ptr<LabyrinthExit>& Labyrinth::GetExit() { return exit; }

const std::vector<std::vector<std::shared_ptr<LabyrinthElement>>>&
Labyrinth::GetElements() const {
    return elements;
}

const MaxrEngine::Vector2Di& Labyrinth::GetStartCell() const {
    return startCell;
}

void Labyrinth::SetCenterPosition(const MaxrEngine::Vector2Df newPosition) {
    auto* transform =
        gameObject->GetComponent<MaxrEngine::TransformComponent>();
    transform->SetWorldPosition(newPosition);
}
const std::vector<MaxrEngine::Vector2Di>& Labyrinth::GetGenerationDeadEnds()
    const {
    return generationDeadEnd;
}
const std::vector<std::vector<bool>>& Labyrinth::GetIsTileWalkable() const {
    return isTileWalkable;
}
const MaxrEngine::Vector2Df Labyrinth::GetCellCoordinates(
    const MaxrEngine::Vector2Di& cell) {
    auto* transform = elements[cell.x][cell.y]
                          ->GetGameObject()
                          ->GetComponent<MaxrEngine::TransformComponent>();
    return transform->GetWorldPosition();
}
}  // namespace Roguelike
