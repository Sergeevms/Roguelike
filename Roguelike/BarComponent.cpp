#include "BarComponent.h"

#include <cmath>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"

#include "Component.h"
#include "GameObject.h"
#include "Logger.h"
#include "RenderSystem.h"
#include "Utility.h"
#include "Vector.h"

namespace Roguelike {
const BarComponent::BarComponentParameters BarComponent::defaultBarParameters{
    .centerOffset = {0.0F, 0.0F},
    .barSize = {1.0F, 0.0F},
    .barColor = sf::Color::White,
    .maxAmount = 1.0F,
    .borderSize = 0.0F};
BarComponent::BarComponent(MaxrEngine::GameObject* gameObject,
                           const BarComponentParameters& parameters)
    : Component(gameObject),
      centerOffset(parameters.centerOffset),
      barSize(parameters.barSize),
      barColor(parameters.barColor),
      maxAmount(parameters.maxAmount),
      currentAmount(parameters.maxAmount),
      borderSize(parameters.borderSize) {}

void BarComponent::Render() {
    if (maxAmount <= 0.0F) {
        LOG_WARN("Bars maxAmount should be positive");
        return;
    }
    const auto& objectPosition =
        gameObject->GetComponent<MaxrEngine::TransformComponent>()
            ->GetWorldPosition();
    auto barTopLeft = objectPosition + centerOffset - Half(barSize);
    const MaxrEngine::Vector2Df filledBarSize = {
        barSize.x * currentAmount / maxAmount, barSize.y};

    if (abs(borderSize) > 0.0F) {
        sf::RectangleShape borderShape(Convert<sf::Vector2f>(barSize));
        borderShape.setFillColor(sf::Color::Transparent);
        borderShape.setOutlineColor(barColor);
        borderShape.setOutlineThickness(borderSize);
        borderShape.setPosition(Convert<sf::Vector2f>(barTopLeft));
        MaxrEngine::RenderSystem::Instance()->Render(borderShape);
    }
    sf::RectangleShape barShape(Convert<sf::Vector2f>(filledBarSize));
    barShape.setFillColor(barColor);
    barShape.setPosition(Convert<sf::Vector2f>(barTopLeft));
    MaxrEngine::RenderSystem::Instance()->Render(barShape);
}

MaxrEngine::Vector2Df BarComponent::GetCenterOffset() const {
    return centerOffset;
}

void BarComponent::SetCenterOffset(
    const MaxrEngine::Vector2Df& newCenterOffset) {
    centerOffset = newCenterOffset;
}

MaxrEngine::Vector2Df BarComponent::GetBarSize() const { return barSize; }

void BarComponent::SetBarSize(const MaxrEngine::Vector2Df& newBarSize) {
    barSize = newBarSize;
}
sf::Color BarComponent::GetBarColor() const { return barColor; }

void BarComponent::SetBarColor(const sf::Color newBarColor) {
    barColor = newBarColor;
}

float BarComponent::GetMaxAmount() const { return maxAmount; }

void BarComponent::SetMaxAmount(const float newMaxAmount) {
    if (newMaxAmount <= 0.0F) {
        LOG_WARN("Bars maxAmount should be positive");
        return;
    }
    maxAmount = newMaxAmount;
}

float BarComponent::GetCurrentAmount() const { return currentAmount; }

void BarComponent::SetCurrentAmount(const float newCurrentAmount) {
    currentAmount = newCurrentAmount;
}

float BarComponent::GetBorderSize() const { return borderSize; }

void BarComponent::SetBorderSize(const float newBorderSize) {
    borderSize = newBorderSize;
}
}  // namespace Roguelike