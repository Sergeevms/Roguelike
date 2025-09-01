#include "pch.h"

#include "BoxColliderComponent.h"

#include "SFML/Graphics/Rect.hpp"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace MaxrEngine {
BoxColliderComponent::BoxColliderComponent(GameObject* gameObject,
                                           const Vector2Df& size)
    : ColliderComponent(gameObject) {
    transform = gameObject->GetComponent<TransformComponent>();
    if (transform == nullptr) {
        gameObject->RemoveComponent(this);
        PhysicsSystem::Instance()->Unsubscribe(this);
        return;
    }
    SetSize(size);
}

void BoxColliderComponent::Update(const float deltaTime) {
    UpdateBoundsPosition();
}

void MaxrEngine::BoxColliderComponent::SetSize(const Vector2Df& newSize) {
    bounds.width = newSize.x;
    bounds.height = newSize.y;
    UpdateBoundsPosition();
}

void BoxColliderComponent::UpdateBoundsPosition() {
    const Vector2Df boundsCenterOffset = {bounds.width / 2.0F,
                                          bounds.height / 2.0F};
    const Vector2Df topLeft =
        transform->GetWorldPosition() - boundsCenterOffset;
    bounds.left = topLeft.x;
    bounds.top = topLeft.y;
}
}  // namespace MaxrEngine