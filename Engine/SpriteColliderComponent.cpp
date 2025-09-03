#include "pch.h"

#include "SpriteColliderComponent.h"

#include "ColliderDebugRender.h"
#include "GameObject.h"
#include "Logger.h"
#include "PhysicsSystem.h"
#include "SpriteRendererComponent.h"

namespace MaxrEngine {
SpriteColliderComponent::SpriteColliderComponent(GameObject* gameObject)
    : ColliderComponent(gameObject), sprite(nullptr) {
    auto* spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
    if (spriteRenderer == nullptr) {
        LOG_ERROR(
            "SpriteRendererComponent required to SpriteColliderComponent.");
        gameObject->RemoveComponent(this);
        PhysicsSystem::Instance()->Unsubscribe(this);
        return;
    }

    sprite = spriteRenderer->GetSprite();
}

SpriteColliderComponent::~SpriteColliderComponent() {
    PhysicsSystem::Instance()->Unsubscribe(this);
}
// NOLINTBEGIN(misc-unused-parameters) : overrided virtual method
void SpriteColliderComponent::Update(float deltaTime) {
    bounds = sprite->getGlobalBounds();
}
// NOLINTEND(misc-unused-parameters)

}  // namespace MaxrEngine