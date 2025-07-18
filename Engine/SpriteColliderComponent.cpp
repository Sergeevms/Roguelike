#include "pch.h"

#include "SpriteColliderComponent.h"

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "GameObject.h"
#include "Logger.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"

namespace MaxrEngine {
SpriteColliderComponent::SpriteColliderComponent(GameObject* gameObject)
    : ColliderComponent(gameObject), sprite(nullptr) {
    auto* spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
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
    PhysicsSystem::Instance()->Unsubscribe(this);
}
// NOLINTBEGIN(misc-unused-parameters) : overrided virtual method
void SpriteColliderComponent::Update(float deltaTime) {
    bounds = sprite->getGlobalBounds();
}
// NOLINTEND(misc-unused-parameters)

void SpriteColliderComponent::Render() {
    constexpr float outlineThickness = 4.0F;
    sf::RectangleShape rectangle(sf::Vector2f(bounds.width, bounds.height));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setPosition(bounds.left, bounds.top);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(outlineThickness);

    RenderSystem::Instance()->Render(rectangle);
}
}  // namespace MaxrEngine