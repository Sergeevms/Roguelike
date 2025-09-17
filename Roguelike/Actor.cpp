#include "Actor.h"

#include <memory>

#include "ActorComponent.h"
#include "ActorMovementComponent.h"
#include "ArmorBarComponent.h"
#include "ArmorComponent.h"
#include "BlockComponent.h"
#include "BoxColliderComponent.h"
#include "ColliderDebugRender.h"
#include "GameObjectContainer.h"
#include "HealthBarComponent.h"
#include "HealthComponent.h"
#include "ISaveable.h"
#include "OffsetSpriteRendererComponent.h"
#include "ResourceSystem.h"
#include "RigidBodyComponent.h"
#include "Settings.h"
#include "SpriteAnimationComponent.h"
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
        parameters.healthBarParameters,
        static_cast<int>(Settings::RenderLayers::UI1));
    healthBar->SetHealthComponent(healthComponent);

    // Add sprite component, animation component
    const auto& defaultAnimation =
        parameters.animations.at(parameters.defaultAnimationName);
    const auto* texture =
        MaxrEngine::ResourceSystem::Instance()->GetTextureMapElementShared(
            defaultAnimation.textureMapName, 0);
    auto render = gameObject->AddComponent<OffsetSpriteRendererComponent>();
    render->SetLayer(static_cast<int>(Settings::RenderLayers::Actors));
    render->SetTexture(*texture, parameters.spriteOffsetParameters);
    render->SetPixelSize(Convert<MaxrEngine::Vector2Di>(parameters.size));

    auto animationComponent =
        gameObject->AddComponent<MaxrEngine::SpriteAnimationComponent>();
    for (const auto& animationPair : parameters.animations) {
        animationComponent->AddAnimation(
            animationPair.first, animationPair.second,
            animationPair.first == parameters.defaultAnimationName);
    }

    // Add movement, Collider and Rigid body components
    gameObject->AddComponent<ActorMovementComponent>(parameters.movementSpeed);
    gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();
    auto collidder = gameObject->AddComponent<MaxrEngine::BoxColliderComponent>(
        MaxrEngine::Vector2Df(parameters.size.x, parameters.size.y));
    gameObject->AddComponent<MaxrEngine::ColliderDebugRender>(
        collidder, static_cast<int>(Settings::RenderLayers::Debug));
    if (parameters.haveBlock) {
        gameObject->AddComponent<BlockComponent>(
            parameters.blockParameters,
            static_cast<int>(Settings::RenderLayers::UI2));
    }
    if (parameters.haveArmor) {
        auto armorComponent = gameObject->AddComponent<ArmorComponent>(
            parameters.armorParameters);
        auto armorBar = gameObject->AddComponent<ArmorBarComponent>(
            parameters.armorBarParameters,
            static_cast<int>(Settings::RenderLayers::UI1));
        armorBar->SetArmorComponent(armorComponent);
    }
}
void Roguelike::Actor::SaveImpl(std::shared_ptr<ActorSave> save) const {
    if (auto* healthComponent = gameObject->GetComponent<HealthComponent>()) {
        save->healthSave = healthComponent->Save();
    }
    if (auto* armorComponent = gameObject->GetComponent<ArmorComponent>()) {
        save->armorSave = armorComponent->Save();
    }
    if (auto* actorComponent = gameObject->GetComponent<ActorComponent>()) {
        save->actorGroupID = actorComponent->GetGroupID();
    }
}
void Roguelike::Actor::LoadImpl(std::shared_ptr<const ActorSave> save) {
    if (auto* healthComponent = gameObject->GetComponent<HealthComponent>()) {
        healthComponent->Load(save->healthSave);
    }
    if (auto* armorComponent = gameObject->GetComponent<ArmorComponent>()) {
        armorComponent->Load(save->armorSave);
    }
    if (auto* actorComponent = gameObject->GetComponent<ActorComponent>()) {
        actorComponent->SetGroupID(save->actorGroupID);
    }
}
}  // namespace Roguelike