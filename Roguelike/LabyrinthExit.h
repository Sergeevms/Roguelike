#pragma once
#include "Floor.h"
#include "Vector.h"

namespace Roguelike {
/** Class for organizing exit from Labyrinth - Floor with trigger contained in
 * SpriteColliderComponent*/
class LabyrinthExit : public Floor {
   public:
    LabyrinthExit(MaxrEngine::Vector2Df position, int textureIndex,
                  MaxrEngine::Vector2Di size);
};
}  // namespace Roguelike
