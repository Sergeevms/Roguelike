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
    explicit HealthBarComponent(
        MaxrEngine::GameObject* gameObject,
        const Parameters& parameters = defaultBarParameters,
        const int renderLayer = 0);

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
