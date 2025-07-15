#include "pch.h"

#include "SpriteColliderComponent.h"

#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"

namespace MaxrEngine {
SpriteColliderComponent::SpriteColliderComponent(GameObject* gameObject)
    : ColliderComponent(gameObject), sprite(nullptr) {
    auto spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
    if (spriteRenderer == nullptr) {
        LOG_ERROR(
            "SpriteRendererComponent required to SpriteColliderComponent.");
        gameObject->RemoveComponent(this);
        return;
    }

    sprite = spriteRenderer->GetSprite();
    PhysicsSystem::Instance()->Subscribe(this);
}

SpriteColliderComponent::~SpriteColliderComponent() {
    if (&bounds != nullptr) {
        std::destroy_at(&bounds);
    }
    PhysicsSystem::Instance()->Unsubscribe(this);
}

void SpriteColliderComponent::Update(float deltaTime) {
    bounds = sprite->getGlobalBounds();
}

void SpriteColliderComponent::Render() {
    sf::RectangleShape rectangle(sf::Vector2f(bounds.width, bounds.height));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setPosition(bounds.left, bounds.top);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(4.f);

    RenderSystem::Instance()->Render(rectangle);
}
}  // namespace MaxrEngine