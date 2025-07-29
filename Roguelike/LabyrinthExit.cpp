#include "LabyrinthExit.h"

#include "Floor.h"
#include "GameObject.h"
#include "SpriteColliderComponent.h"
#include "Vector.h"

namespace Roguelike {
LabyrinthExit::LabyrinthExit(MaxrEngine::Vector2Df position, int textureIndex,
                             MaxrEngine::Vector2Di size)
    : Floor(position, textureIndex, size) {
    auto exitTrigger =
        gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();
    exitTrigger->SetTrigger(true);
}
}  // namespace Roguelike