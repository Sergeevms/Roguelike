#include "PerceptionComponentDebugDraw.h"

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"

#include "Component.h"
#include "GameObject.h"
#include "IRenderable.h"
#include "Logger.h"
#include "PerceptionComponent.h"
#include "RenderSystem.h"
#include "Utility.h"
#include "Vector.h"

namespace Roguelike {
constexpr float fullCircleAngle = 360.0F;

PerceptionComponentDebugDraw::PerceptionComponentDebugDraw(
    MaxrEngine::GameObject* gameObject, const int layer,
    const int arcLinesCount)
    : Component(gameObject), IRenderable(layer), arcLinesCount(arcLinesCount) {
    perceptionComponent =
        gameObject->GetComponentSharedPtr<PerceptionComponent>();
    if (perceptionComponent.expired()) {
        LOG_WARN("PerceptionComponentDebugDraw needs PerceptionComponent");
        gameObject->RemoveComponent(this);
        return;
    }
}

void PerceptionComponentDebugDraw::Update(float deltaTime) {}

void PerceptionComponentDebugDraw::Render() {
    constexpr float outlineThickness = -2.0F;
    if (auto perception = perceptionComponent.lock()) {
        const auto& position =
            gameObject->GetComponent<MaxrEngine::TransformComponent>()
                ->GetWorldPosition();
        // Draw sense zone
        sf::CircleShape senseZone(perception->GetSenseRadius());
        senseZone.setFillColor(sf::Color::Transparent);
        senseZone.setOutlineColor(sf::Color::Red);
        senseZone.setOutlineThickness(outlineThickness);
        senseZone.setPosition(
            Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position));
        auto rect = senseZone.getLocalBounds();
        senseZone.setOrigin(Half(rect.width), Half(rect.height));
        MaxrEngine::RenderSystem::Instance()->Render(senseZone, layer);

        // Draw vision direction
        sf::VertexArray visionDirection(sf::PrimitiveType::LineStrip, 2);
        auto direction = Normalized(perception->GetVisionDirection()) *
                         perception->GetVisionRadius();
        visionDirection[0] =
            sf::Vertex(Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position),
                       sf::Color::Green);
        visionDirection[1] = sf::Vertex(
            Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position + direction),
            sf::Color::Green);
        MaxrEngine::RenderSystem::Instance()->Render(visionDirection, layer);

        // Draw vision area, cone or circle depending on visionAngle
        auto visionAngle = perception->GetVisionAngle();
        if (visionAngle < fullCircleAngle) {
            // Additional 3 vertexex for cone center (as start and end) and arc
            // start
            sf::VertexArray visionCone(sf::PrimitiveType::LineStrip);
            // Set up start point
            visionCone.append(sf::Vertex(
                Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position),
                sf::Color::Yellow));
            // Rotate direction to get first point of arc
            Rotate(direction, Half(-visionAngle));
            // Set first point of arc
            visionCone.append(sf::Vertex(
                Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position +
                                                             direction),
                sf::Color::Yellow));

            const auto angleStep =
                visionAngle / static_cast<float>(arcLinesCount);
            // Draw arc rotating direction vector
            for (int i = 0; i < arcLinesCount; ++i) {
                Rotate(direction, angleStep);
                visionCone.append(sf::Vertex(
                    Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position +
                                                                 direction),
                    sf::Color::Yellow));
            }
            // Add start point to finish cone and render it
            visionCone.append(sf::Vertex(
                Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position),
                sf::Color::Yellow));
            MaxrEngine::RenderSystem::Instance()->Render(visionCone, layer);
        } else {
            // If vision angle is 360 degree or more, just render it as circle
            sf::CircleShape visionZone(perception->GetVisionRadius());
            visionZone.setFillColor(sf::Color::Transparent);
            visionZone.setOutlineColor(sf::Color::Yellow);
            visionZone.setOutlineThickness(outlineThickness);
            visionZone.setPosition(
                Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position));
            MaxrEngine::RenderSystem::Instance()->Render(visionZone, layer);
        }
    } else {
        LOG_WARN("PerceptionComponentDebugDraw needs PerceptionComponent");
    }
}

void PerceptionComponentDebugDraw::setArcPointCount(
    const int newArcPointsCount) {
    arcLinesCount = newArcPointsCount;
}
int PerceptionComponentDebugDraw::getArcPointCount() const {
    return arcLinesCount;
}
}  // namespace Roguelike