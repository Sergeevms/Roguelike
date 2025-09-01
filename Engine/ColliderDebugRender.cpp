#include "pch.h"

#include "ColliderDebugRender.h"

#include <memory>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"

#include "ColliderComponent.h"
#include "Component.h"
#include "GameObject.h"
#include "IRenderable.h"
#include "RenderSystem.h"

namespace MaxrEngine {
ColliderDebugRender::ColliderDebugRender(
    GameObject* gameObject, std::shared_ptr<ColliderComponent> collider,
    const int layer)
    : Component(gameObject), IRenderable(layer), colliderPtr(collider) {}
void ColliderDebugRender::Update(float deltaTime) {}
void ColliderDebugRender::Render() {
    if (auto collider = colliderPtr.lock()) {
        const auto& bounds = collider->bounds;
        constexpr float outlineThickness = 4.0F;
        sf::RectangleShape rectangle(sf::Vector2f(bounds.width, bounds.height));
        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setPosition(bounds.left, bounds.top);
        rectangle.setOutlineColor(sf::Color::White);
        rectangle.setOutlineThickness(outlineThickness);

        RenderSystem::Instance()->Render(rectangle, layer);
    } else {
        gameObject->RemoveComponent(this);
    }
}
}  // namespace MaxrEngine
