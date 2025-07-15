#pragma once
#include "GameObject.h"
#include "GameObjectContainer.h"

namespace Roguelike {
class Floor : public GameObjectContainer {
   public:
    Floor(MaxrEngine::Vector2Df position, int textureIndex,
          MaxrEngine::Vector2Di size);
};
}  // namespace Roguelike
