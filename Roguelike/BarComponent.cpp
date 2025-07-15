#include "BarComponent.h"

#include "GameObject.h"
#include "Logger.h"
#include "RenderSystem.h"

namespace Roguelike {
Roguelike::BarComponent::BarComponent(MaxrEngine::GameObject* gameObject,
                                      MaxrEngine::Vector2Df centerOffset,
                                      MaxrEngine::Vector2Df barSize,
                                      sf::Color barColor, float borderSize,
                                      float maxAmount)
    : Component(gameObject),
      centerOffset(centerOffset),
      barSize(barSize),
      barColor(barColor),
      borderSize(borderSize),
      maxAmount(maxAmount),
      currentAmount(maxAmount) {}

void BarComponent::Render() {
    if (maxAmount <= 0.f) {
        LOG_WARN("Bars maxAmount should be positive");
        return;
    }
    auto objectPosition =
        gameObject->GetComponent<MaxrEngine::TransformComponent>()
            ->GetWorldPosition();
    auto barTopLeft = objectPosition + centerOffset - barSize * 0.5f;
    MaxrEngine::Vector2Df filledBarSize = {
        barSize.x * currentAmount / maxAmount, barSize.y};

    if (abs(borderSize) > 0.f) {
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
    if (newMaxAmount <= 0.f) {
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