#pragma once
#include "GameObjectContainer.h"
#include "Vector.h"

namespace Roguelike {
class Wall : public GameObjectContainer {
   public:
    Wall(const MaxrEngine::Vector2Df position, int textureIndex,
         const MaxrEngine::Vector2Di size);
};
}  // namespace Roguelike
