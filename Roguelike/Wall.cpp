#include "Wall.h"

#include "ColliderDebugRender.h"
#include "LabyrinthElement.h"
#include "ResourceSystem.h"
#include "RigidBodyComponent.h"
#include "Settings.h"
#include "SpriteColliderComponent.h"
#include "SpriteOpaqueComponent.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike {
Wall::Wall(const MaxrEngine::Vector2Df position, int textureIndex,
           const MaxrEngine::Vector2Di size)
    : LabyrinthElement("Wall") {
    auto* transform =
        gameObject->GetComponent<MaxrEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    auto spriteRenderer =
        gameObject->AddComponent<MaxrEngine::SpriteRendererComponent>(
            static_cast<int>(Settings::RenderLayers::Walls));
    spriteRenderer->SetTexture(
        *MaxrEngine::ResourceSystem::Instance()->GetTextureMapElementShared(
            "WallTextures", textureIndex));
    spriteRenderer->SetPixelSize(size.x, size.y);

    auto body = gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();
    body->SetKinematic(true);

    auto collider =
        gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();
    gameObject->AddComponent<MaxrEngine::ColliderDebugRender>(
        collider, static_cast<int>(Settings::RenderLayers::Debug));

    gameObject->AddComponent<SpriteOpaqueComponent>(
        static_cast<int>(Settings::RenderLayers::Debug));
}
}  // namespace Roguelike