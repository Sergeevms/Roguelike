#include "Floor.h"

#include "LabyrinthElement.h"
#include "ResourceSystem.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike {
Floor::Floor(MaxrEngine::Vector2Df position, int textureIndex,
             MaxrEngine::Vector2Di size)
    : LabyrinthElement("Floor") {
    auto* transform =
        gameObject->GetComponent<MaxrEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    auto sprite =
        gameObject->AddComponent<MaxrEngine::SpriteRendererComponent>();
    sprite->SetTexture(
        *MaxrEngine::ResourceSystem::Instance()->GetTextureMapElementShared(
            "FloorTextures", textureIndex));
    sprite->SetPixelSize(size.x, size.y);
}
}  // namespace Roguelike