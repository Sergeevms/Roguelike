#include "NavigationSystemDebugRendererComponent.h"

#include <algorithm>
#include <limits>
#include <memory>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Vector2.hpp"

#include "Component.h"
#include "GameObject.h"
#include "IObserver.h"
#include "IRenderable.h"
#include "NavigationSystem.h"
#include "RenderSystem.h"
#include "Vector.h"

namespace Roguelike {
NavigationSystemDebugRendererComponent::NavigationSystemDebugRendererComponent(
    MaxrEngine::GameObject* gameObject, const int layer)
    : Component(gameObject), IRenderable(layer) {}

void NavigationSystemDebugRendererComponent::Update(float deltaTime) {}

void NavigationSystemDebugRendererComponent::Render() {
    MaxrEngine::RenderSystem::Instance()->Render(sprite, layer);
}

void NavigationSystemDebugRendererComponent::Notify(
    std::shared_ptr<MaxrEngine::IObservable> observable) {
    if (auto navigationSystem =
            std::dynamic_pointer_cast<NavigationSystem>(observable)) {
        constexpr float infinity = std::numeric_limits<float>::infinity();
        MaxrEngine::Vector2Df TopLeft = {infinity, infinity};
        MaxrEngine::Vector2Df BottomRight = {-infinity, -infinity};
        for (auto& node : navigationSystem->nodes) {
            auto& coordinates = node->coordinates;
            TopLeft.x = std::min(TopLeft.x, coordinates.x);
            TopLeft.y = std::min(TopLeft.y, coordinates.y);
            BottomRight.x = std::max(BottomRight.x, coordinates.x);
            BottomRight.y = std::max(BottomRight.y, coordinates.y);
        }
        constexpr int nodeRadius = 4;
        TopLeft.x -= nodeRadius;
        TopLeft.y -= nodeRadius;
        sf::Vector2i size = {
            static_cast<int>(BottomRight.x - TopLeft.x) + nodeRadius,
            static_cast<int>(BottomRight.y - TopLeft.y) + nodeRadius};
        texture.create(size.x, size.y);
        size.y *= -1;
        auto view =
            sf::View(sf::FloatRect(MaxrEngine::Convert<sf::Vector2f>(TopLeft),
                                   MaxrEngine::Convert<sf::Vector2f>(size)));
        constexpr float half = 0.5F;
        view.setCenter(
            MaxrEngine::Convert<sf::Vector2f>(half * (TopLeft + BottomRight)));
        texture.setView(view);
        sf::CircleShape nodeCircle(nodeRadius);
        nodeCircle.setRadius(nodeRadius);
        nodeCircle.setOrigin({half * nodeRadius, half * nodeRadius});
        nodeCircle.setFillColor(sf::Color::Cyan);
        sf::VertexArray lineArray(sf::PrimitiveType::Lines);
        sf::Vertex vertex;
        vertex.color = sf::Color::Cyan;
        for (auto& node : navigationSystem->nodes) {
            auto coordinates = Convert<sf::Vector2f>(node->coordinates);
            nodeCircle.setPosition(coordinates);
            texture.draw(nodeCircle);
            for (auto& edge : node->edges) {
                vertex.position = coordinates;
                lineArray.append(vertex);
                vertex.position =
                    MaxrEngine::Convert<sf::Vector2f>(edge.node->coordinates);
                lineArray.append(vertex);
            }
        }
        texture.draw(lineArray);
        sprite.setTexture(texture.getTexture());
        sprite.setPosition(Convert<sf::Vector2f>(TopLeft));
    }
}

}  // namespace Roguelike