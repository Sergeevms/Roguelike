#pragma once
#include "LabyrinthElement.h"
#include "Vector.h"

namespace Roguelike {
class Floor : public LabyrinthElement {
   public:
    Floor(MaxrEngine::Vector2Df position, int textureIndex,
          MaxrEngine::Vector2Di size);
};
}  // namespace Roguelike
