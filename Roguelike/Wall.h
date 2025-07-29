#pragma once
#include "LabyrinthElement.h"
#include "Vector.h"

namespace Roguelike {
class Wall : public LabyrinthElement {
   public:
    Wall(const MaxrEngine::Vector2Df position, int textureIndex,
         const MaxrEngine::Vector2Di size);
};
}  // namespace Roguelike
