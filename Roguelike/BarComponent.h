#pragma once
#include "SFML/Graphics/Color.hpp"

#include "Component.h"
#include "GameObject.h"
#include "IRenderable.h"
#include "Vector.h"

namespace Roguelike {
class BarComponent : public MaxrEngine::Component,
                     public MaxrEngine::IRenderable {
   public:
    struct Parameters {
        MaxrEngine::Vector2Df centerOffset;
        MaxrEngine::Vector2Df barSize;
        sf::Color barColor;
        float borderSize;
        float maxAmount = 0.0F;
    };
    explicit BarComponent(MaxrEngine::GameObject* gameObject,
                          const Parameters& parameters = defaultBarParameters);

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
    const static Parameters defaultBarParameters;
    MaxrEngine::Vector2Df centerOffset;
    MaxrEngine::Vector2Df barSize;
    sf::Color barColor;
    float maxAmount;
    float currentAmount;
    float borderSize;
};
}  // namespace Roguelike
