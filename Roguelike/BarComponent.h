#pragma once
#include "SFML/Graphics/Color.hpp"

#include "Component.h"
#include "Vector.h"

namespace Roguelike {
class BarComponent : public MaxrEngine::Component {
   public:
    explicit BarComponent(MaxrEngine::GameObject* gameObject,
                          MaxrEngine::Vector2Df centerOffset = {0.0F, 0.0F},
                          MaxrEngine::Vector2Df barSize = {1.0F, 0.0F},
                          sf::Color barColor = sf::Color::White,
                          float borderSize = 0.0F, float maxAmount = 1.0F);

    void Update(float deltaTime) override = 0;
    void Render() override;

    MaxrEngine::Vector2Df GetCenterOffset() const;
    void SetCenterOffset(const MaxrEngine::Vector2Df& newCenterOffset);

    MaxrEngine::Vector2Df GetBarSize() const;
    void SetBarSize(const MaxrEngine::Vector2Df& newBarSize);

    sf::Color GetBarColor() const;
    void SetBarColor(const sf::Color newBarColor);

    float GetMaxAmount() const;
    void SetMaxAmount(const float newMaxAmount);

    float GetCurrentAmount() const;
    void SetCurrentAmount(const float newCurrentAmount);

    float GetBorderSize() const;
    void SetBorderSize(const float newBorderSize);

   protected:
    MaxrEngine::Vector2Df centerOffset;
    MaxrEngine::Vector2Df barSize;
    sf::Color barColor;
    float maxAmount;
    float currentAmount;
    float borderSize;
};
}  // namespace Roguelike
