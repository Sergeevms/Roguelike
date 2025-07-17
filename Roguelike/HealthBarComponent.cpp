#include "HealthBarComponent.h"

#include <memory>

#include "SFML/Graphics/Color.hpp"

#include "BarComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "IObserver.h"
#include "Vector.h"

namespace Roguelike {
HealthBarComponent::HealthBarComponent(MaxrEngine::GameObject* gameObject,
                                       MaxrEngine::Vector2Df centerOffset,
                                       MaxrEngine::Vector2Df barSize,
                                       float borderSize, sf::Color barColor)
    : BarComponent(gameObject, centerOffset, barSize, barColor, borderSize) {}

void HealthBarComponent::Update(float deltTime) {}

void HealthBarComponent::Render() {
    if (!healthComponent.expired()) {
        BarComponent::Render();
    }
}

void HealthBarComponent::Notify(
    std::shared_ptr<MaxrEngine::IObservable> observable) {
    auto lockedHealthComponent = healthComponent.lock();
    if (lockedHealthComponent &&
        lockedHealthComponent ==
            std::dynamic_pointer_cast<HealthComponent>(observable)) {
        maxAmount = lockedHealthComponent->GetMaxHealth();
        currentAmount = lockedHealthComponent->GetCurrentHealth();
    }
}

void HealthBarComponent::SetHealthComponent(
    std::shared_ptr<HealthComponent> newHealthComponent) {
    newHealthComponent->AddObserver(weak_from_this());
    healthComponent = newHealthComponent;
    maxAmount = newHealthComponent->GetMaxHealth();
    currentAmount = newHealthComponent->GetCurrentHealth();
}

std::weak_ptr<HealthComponent> HealthBarComponent::GetHealthComponent() const {
    return healthComponent;
}
}  // namespace Roguelike