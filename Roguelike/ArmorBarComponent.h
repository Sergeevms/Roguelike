#pragma once
#include "ArmorComponent.h"
#include "BarComponent.h"
#include "IObserver.h"
namespace Roguelike {
class ArmorBarComponent
    : public BarComponent,
      public MaxrEngine::IObserver,
      public std::enable_shared_from_this<ArmorBarComponent> {
   public:
    ArmorBarComponent(MaxrEngine::GameObject* gameObject,
                      MaxrEngine::Vector2Df centerOffset = {0.f, 0.f},
                      MaxrEngine::Vector2Df barSize = {1.f, 4.f},
                      float borderSize = -1.f,
                      sf::Color barColor = sf::Color::Yellow);

    void Update(float deltTime) override;
    void Render() override;

    void Notify(std::shared_ptr<MaxrEngine::IObservable> observable);

    void SetArmorComponent(std::shared_ptr<ArmorComponent> newArmorComponent);
    std::weak_ptr<ArmorComponent> GetArmorComponent() const;

   protected:
    std::weak_ptr<ArmorComponent> armorComponent;
};
}  // namespace Roguelike
