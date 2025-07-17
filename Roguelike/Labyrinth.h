#pragma once
#include <memory>
#include <vector>

#include "Floor.h"
#include "GameObjectContainer.h"
#include "Vector.h"
#include "Wall.h"

namespace Roguelike {
class Labyrinth : public GameObjectContainer {
   public:
    Labyrinth();
    const std::vector<std::shared_ptr<Wall>>& GetWalls() const;
    const std::vector<std::shared_ptr<Floor>>& GetFloors() const;
    void SetCenterPosition(const MaxrEngine::Vector2Df newPosition);
    friend class LabyrinthBuilder;

   private:
    std::vector<std::shared_ptr<Wall>> walls;
    std::vector<std::shared_ptr<Floor>> floors;
};
}  // namespace Roguelike
