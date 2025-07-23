#pragma once
#include <memory>

#include "ArmorComponent.h"
#include "BarComponent.h"
#include "GameObject.h"
#include "IObserver.h"

namespace Roguelike {
class ArmorBarComponent
    : public BarComponent,
      public MaxrEngine::IObserver,
      public std::enable_shared_from_this<ArmorBarComponent> {
   public:
    explicit ArmorBarComponent(
        MaxrEngine::GameObject* gameObject,
        const Parameters& parameters = defaultBarParameters);

    void Update(float deltTime) override;
    void Render() override;

    void Notify(std::shared_ptr<MaxrEngine::IObservable> observable) override;

    void SetArmorComponent(std::shared_ptr<ArmorComponent> newArmorComponent);
    std::weak_ptr<ArmorComponent> GetArmorComponent() const;

   protected:
    std::weak_ptr<ArmorComponent> armorComponent;
};
}  // namespace Roguelike
