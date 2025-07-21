#pragma once
#include "SFML/Graphics/Color.hpp"

#include "Component.h"
#include "GameObject.h"
#include "Vector.h"

namespace Roguelike {
class BarComponent : public MaxrEngine::Component {
   public:
    struct BarComponentParameters {
        MaxrEngine::Vector2Df centerOffset;
        MaxrEngine::Vector2Df barSize;
        sf::Color barColor;
        float maxAmount;
        float borderSize;
    };
    explicit BarComponent(
        MaxrEngine::GameObject* gameObject,
        const BarComponentParameters& parameters = defaultBarParameters);

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
    const static BarComponentParameters defaultBarParameters;
    MaxrEngine::Vector2Df centerOffset;
    MaxrEngine::Vector2Df barSize;
    sf::Color barColor;
    float maxAmount;
    float currentAmount;
    float borderSize;
};
}  // namespace Roguelike
