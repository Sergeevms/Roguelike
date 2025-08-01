#include "BlockComponent.h"

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

#include "Component.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "MovementComponent.h"
#include "RenderSystem.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike {
const BlockComponent::Parameters BlockComponent::defaultParameters = {
    .damageReduction = 1.0F,
    .speedCoefficient = 0.9F,
    .centerOffset = {0.0F, 0.0F},
    .iconRadius = 4.0F,
    .iconColor = sf::Color::Green};

BlockComponent::BlockComponent(MaxrEngine::GameObject* gameObject,
                               const Parameters& parameters)
    : Component(gameObject),
      damageReduction(parameters.damageReduction),
      speedCoefficient(parameters.speedCoefficient),
      centerOffset(parameters.centerOffset),
      iconRadius(parameters.iconRadius),
      iconColor(parameters.iconColor) {};
// NOLINTBEGIN(misc-unused-parameters) : inhereted method with parameter
void BlockComponent::Update(float deltaTime) {
    // Check that has input ob blocking action
    if (const auto* input =
            gameObject->GetComponent<MaxrEngine::InputComponent>()) {
        auto isBlockingInput = input->getBlock();
        // Check combinations on input blocking and current blocking state
        if (isBlocking && !isBlockingInput) {
            // Was blocking, now released - return speed to normal
            if (auto* movementComponent =
                    gameObject->GetComponent<MaxrEngine::MovementComponent>()) {
                auto newSpeed =
                    1.0F / speedCoefficient * movementComponent->GetSpeed();
                movementComponent->SetSpeed(newSpeed);
            }
            isBlocking = isBlockingInput;
        } else if (!isBlocking && isBlockingInput) {
            // Wasn't blocking, now started - set speed to reduced
            if (auto* movementComponent =
                    gameObject->GetComponent<MaxrEngine::MovementComponent>()) {
                auto newSpeed =
                    speedCoefficient * movementComponent->GetSpeed();
                movementComponent->SetSpeed(newSpeed);
            }
            isBlocking = isBlockingInput;
        }  // input and current blocking state is equal, nothing to change
    }
}
// NOLINTEND(misc-unused-parameters)
void BlockComponent::Render() {
    if (isBlocking) {
        sf::CircleShape icon(iconRadius);
        icon.setFillColor(iconColor);
        auto* transform =
            gameObject->GetComponent<MaxrEngine::TransformComponent>();
        auto position = transform->GetWorldPosition() + centerOffset;
        icon.setPosition(Convert<sf::Vector2f>(position));
        MaxrEngine::RenderSystem::Instance()->Render(icon);
    }
}
float BlockComponent::ApplyDamage(const float damage) const {
    // Check if isBlocking
    if (!isBlocking) {
        // If not blocking, all damage goes throw
        return damage;
    }
    // If blocking, reduce damage by damageReduction part
    return damage * (1.0F - damageReduction);
}
bool BlockComponent::GetIsBlocking() const { return isBlocking; };

}  // namespace Roguelike