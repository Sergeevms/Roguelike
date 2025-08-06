#include "Actor.h"

#include "ActorComponent.h"
#include "ArmorBarComponent.h"
#include "ArmorComponent.h"
#include "BlockComponent.h"
#include "GameObjectContainer.h"
#include "HealthBarComponent.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
#include "ResourceSystem.h"
#include "RigidBodyComponent.h"
#include "SpriteAnimationComponent.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"
#include "Vector.h"
namespace Roguelike {
Actor::Actor(const Parameters& parameters,
             const MaxrEngine::Vector2Df& position)
    : GameObjectContainer(parameters.actorName) {
    // Set Actor position
    auto* transform =
        gameObject->GetComponent<MaxrEngine::TransformComponent>();
    transform->SetWorldPosition(position);
    gameObject->AddComponent<ActorComponent>(parameters.actorGroupID);
    // Add health and health bar component
    auto healthComponent =
        gameObject->AddComponent<HealthComponent>(parameters.maxHealthAmount);
    auto healthBar = gameObject->AddComponent<HealthBarComponent>(
        parameters.healthBarParameters);
    healthBar->SetHealthComponent(healthComponent);
    // Add sprite component, animation component
    const auto& defaultAnimation =
        parameters.animations.at(parameters.defaultAnimationName);
    const auto* texture =
        MaxrEngine::ResourceSystem::Instance()->GetTextureMapElementShared(
            defaultAnimation.textureMapName, 0);
    auto render =
        gameObject->AddComponent<MaxrEngine::SpriteRendererComponent>();
    render->SetTexture(*texture);
    render->SetPixelSize(parameters.spriteSize);
    auto animationComponent =
        gameObject->AddComponent<MaxrEngine::SpriteAnimationComponent>();
    for (const auto& animationPair : parameters.animations) {
        animationComponent->AddAnimation(
            animationPair.first, animationPair.second,
            animationPair.first == parameters.defaultAnimationName);
    }
    // Add movement, Collider and Rigid body components
    gameObject->AddComponent<MaxrEngine::MovementComponent>(
        parameters.movementSpeed);
    gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();
    gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();
    if (parameters.haveBlock) {
        gameObject->AddComponent<BlockComponent>(parameters.blockParameters);
    }
    if (parameters.haveArmor) {
        auto armorComponent = gameObject->AddComponent<ArmorComponent>(
            parameters.armorParameters);
        auto armorBar = gameObject->AddComponent<ArmorBarComponent>(
            parameters.armorBarParameters);
        armorBar->SetArmorComponent(armorComponent);
    }
}
}  // namespace Roguelike