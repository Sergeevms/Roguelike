#pragma once
#include <memory>

#include "SFML/Graphics/Color.hpp"

#include "BarComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "IObserver.h"
#include "Vector.h"

namespace Roguelike {
class HealthBarComponent
    : public BarComponent,
      public MaxrEngine::IObserver,
      public std::enable_shared_from_this<HealthBarComponent> {
   public:
    explicit HealthBarComponent(MaxrEngine::GameObject* gameObject,
                                MaxrEngine::Vector2Df centerOffset = {0.0F,
                                                                      0.0F},
                                MaxrEngine::Vector2Df barSize = {1.0F, 1.0F},
                                float borderSize = -1.0F,
                                sf::Color barColor = sf::Color::Red);

    void Update(float deltTime) override;
    void Render() override;

    void Notify(std::shared_ptr<MaxrEngine::IObservable> observable) override;

    void SetHealthComponent(
        std::shared_ptr<HealthComponent> newHealthComponent);
    std::weak_ptr<HealthComponent> GetHealthComponent() const;

   protected:
    std::weak_ptr<HealthComponent> healthComponent;
};
}  // namespace Roguelike
