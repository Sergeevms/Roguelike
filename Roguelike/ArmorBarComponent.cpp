#include "ArmorBarComponent.h"

#include <memory>

#include "SFML/Graphics/Color.hpp"

#include "ArmorComponent.h"
#include "BarComponent.h"
#include "GameObject.h"
#include "IObserver.h"
#include "Vector.h"

namespace Roguelike {
ArmorBarComponent::ArmorBarComponent(MaxrEngine::GameObject* gameObject,
                                     MaxrEngine::Vector2Df centerOffset,
                                     MaxrEngine::Vector2Df barSize,
                                     float borderSize, sf::Color barColor)
    : BarComponent(gameObject, centerOffset, barSize, barColor, borderSize) {}
void ArmorBarComponent::Update(float deltTime) {}
void ArmorBarComponent::Render() {
    if (!armorComponent.expired()) {
        BarComponent::Render();
    }
}
void ArmorBarComponent::Notify(
    std::shared_ptr<MaxrEngine::IObservable> observable) {
    auto lockedArmorComponent = armorComponent.lock();
    if (lockedArmorComponent &&
        lockedArmorComponent ==
            std::dynamic_pointer_cast<ArmorComponent>(observable)) {
        maxAmount = lockedArmorComponent->GetMaxArmorPoints();
        currentAmount = lockedArmorComponent->GetCurrentArmorPoints();
    }
}
void ArmorBarComponent::SetArmorComponent(
    std::shared_ptr<ArmorComponent> newArmorComponent) {
    newArmorComponent->AddObserver(weak_from_this());
    armorComponent = newArmorComponent;
    maxAmount = newArmorComponent->GetMaxArmorPoints();
    currentAmount = newArmorComponent->GetCurrentArmorPoints();
}
std::weak_ptr<ArmorComponent> ArmorBarComponent::GetArmorComponent() const {
    return armorComponent;
}
}  // namespace Roguelike