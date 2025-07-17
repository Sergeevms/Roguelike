#include "SpriteOpaqueComponent.h"

#include <memory>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "GameObject.h"
#include "Logger.h"
#include "OpaqueComponent.h"
#include "PerceptionSystem.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"

namespace Roguelike {
constexpr float outlineThickness = -2.0F;
SpriteOpaqueComponent::SpriteOpaqueComponent(MaxrEngine::GameObject* gameObject)
    : OpaqueComponent(gameObject), sprite(nullptr) {
    auto* spriteRenderer =
        gameObject->GetComponent<MaxrEngine::SpriteRendererComponent>();
    if (spriteRenderer == nullptr) {
        LOG_ERROR("SpriteRendererComponent required to SpriteOpaqueComponent.");
        gameObject->RemoveComponent(this);
        return;
    }

    sprite = spriteRenderer->GetSprite();
    PerceptionSystem::Instance()->RegisterOpaqueComponent(this);
}

SpriteOpaqueComponent::~SpriteOpaqueComponent() {
    if (&bounds != nullptr) {
        std::destroy_at(&bounds);
    }
    PerceptionSystem::Instance()->UnregisterOpaqueComponent(this);
}

void SpriteOpaqueComponent::Update(float deltaTime) {
    bounds = sprite->getGlobalBounds();
}

void SpriteOpaqueComponent::Render() {
    OpaqueComponent::Render();
    sf::RectangleShape rectangle(sf::Vector2f(bounds.width, bounds.height));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setPosition(bounds.left, bounds.top);
    rectangle.setOutlineColor(sf::Color::Cyan);
    rectangle.setOutlineThickness(outlineThickness);
    MaxrEngine::RenderSystem::Instance()->Render(rectangle);
}
}  // namespace Roguelike