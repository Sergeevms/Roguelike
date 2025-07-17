#pragma once
#include <memory>

#include "SFML/Graphics/Color.hpp"

#include "ArmorComponent.h"
#include "BarComponent.h"
#include "GameObject.h"
#include "IObserver.h"
#include "Vector.h"

namespace Roguelike {
class ArmorBarComponent
    : public BarComponent,
      public MaxrEngine::IObserver,
      public std::enable_shared_from_this<ArmorBarComponent> {
   public:
    explicit ArmorBarComponent(MaxrEngine::GameObject* gameObject,
                               MaxrEngine::Vector2Df centerOffset = {0.0F,
                                                                     0.0F},
                               MaxrEngine::Vector2Df barSize = {1.0F, 1.0F},
                               float borderSize = -1.0F,
                               sf::Color barColor = sf::Color::Yellow);

    void Update(float deltTime) override;
    void Render() override;

    void Notify(std::shared_ptr<MaxrEngine::IObservable> observable) override;

    void SetArmorComponent(std::shared_ptr<ArmorComponent> newArmorComponent);
    std::weak_ptr<ArmorComponent> GetArmorComponent() const;

   protected:
    std::weak_ptr<ArmorComponent> armorComponent;
};
}  // namespace Roguelike
