#include "Wall.h"

#include "GameObjectContainer.h"
#include "ResourceSystem.h"
#include "RigidBodyComponent.h"
#include "SpriteColliderComponent.h"
#include "SpriteOpaqueComponent.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike {
Wall::Wall(const MaxrEngine::Vector2Df position, int textureIndex,
           const MaxrEngine::Vector2Di size)
    : GameObjectContainer("Wall") {
    auto* transform =
        gameObject->GetComponent<MaxrEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    auto spriteRenderer =
        gameObject->AddComponent<MaxrEngine::SpriteRendererComponent>();
    spriteRenderer->SetTexture(
        *MaxrEngine::ResourceSystem::Instance()->GetTextureMapElementShared(
            "WallTextures", textureIndex));
    spriteRenderer->SetPixelSize(size.x, size.y);

    auto body = gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();
    body->SetKinematic(true);

    gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();

    gameObject->AddComponent<SpriteOpaqueComponent>();
}
}  // namespace Roguelike