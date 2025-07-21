#include "Player.h"

#include "SFML/Graphics/Color.hpp"

#include "ActorComponent.h"
#include "ArmorBarComponent.h"
#include "ArmorComponent.h"
#include "AttackComponent.h"
#include "BarComponent.h"
#include "CameraComponent.h"
#include "GameObjectContainer.h"
#include "HealthBarComponent.h"
#include "HealthComponent.h"
#include "KeyboardInputComponent.h"
#include "MovementComponent.h"
#include "PlayerAttackComponent.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "RigidBodyComponent.h"
#include "Settings.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"
#include "Utility.h"

namespace Roguelike {
Player::Player() : GameObjectContainer("Player") {
    auto* settings = Settings::Instance();

    auto playerRender =
        gameObject->AddComponent<MaxrEngine::SpriteRendererComponent>();
    playerRender->SetTexture(
        *MaxrEngine::ResourceSystem::Instance()->GetTextureMapElementShared(
            "PlayerTextures", 0));
    playerRender->SetPixelSize(settings->playerSize, settings->playerSize);

    auto playerCamera = gameObject->AddComponent<MaxrEngine::CameraComponent>();
    playerCamera->SetWindow(
        &MaxrEngine::RenderSystem::Instance()->GetMainWindow());
    playerCamera->SetBaseResolution(settings->screenWidth,
                                    settings->screenHeight);

    auto input = gameObject->AddComponent<MaxrEngine::KeyboardInputComponent>();

    auto playerMovement =
        gameObject->AddComponent<MaxrEngine::MovementComponent>();
    playerMovement->SetSpeed(settings->playerSpeed);

    auto body = gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();
    body->SetKinematic(false);

    gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();

    auto health =
        gameObject->AddComponent<HealthComponent>(settings->playerHealth);
    const BarComponent::BarComponentParameters healthBarParameters{
        .centerOffset = {0.0F, Half(settings->PlayerSizeF()) +
                                   settings->healthBarDistance},
        .barSize =
            MaxrEngine::Vector2Df(settings->PlayerSizeF(), settings->barHeight),
        .barColor = sf::Color::Red,
        .maxAmount = 1.0F,
        .borderSize = settings->barBorder};
    auto healthBar =
        gameObject->AddComponent<HealthBarComponent>(healthBarParameters);
    healthBar->SetHealthComponent(health);

    const ArmorComponent::ArmorComponentParameters armorParameters = {
        .maxArmorPoints = settings->playerHealth,
        .damageReduction = settings->armorDamageReduction};
    auto armor = gameObject->AddComponent<ArmorComponent>(armorParameters);
    const BarComponent::BarComponentParameters armorBarParameters{
        .centerOffset = {0.0F, Half(settings->PlayerSizeF()) +
                                   settings->armorBarDistance},
        .barSize =
            MaxrEngine::Vector2Df(settings->PlayerSizeF(), settings->barHeight),
        .barColor = sf::Color::Yellow,
        .borderSize = settings->barBorder};
    auto armorBar =
        gameObject->AddComponent<ArmorBarComponent>(armorBarParameters);
    armorBar->SetArmorComponent(armor);
    ;

    auto actorComponent = gameObject->AddComponent<ActorComponent>();
    actorComponent->SetGroupID(ActorsGroups::PlayerGroup);

    const AttackComponent::AtackComponentParameters atackParamteres{
        .cooldown = settings->attackCooldown,
        .damage = settings->attackDamage,
        .range = settings->attackRange};
    auto attackComponent =
        gameObject->AddComponent<PlayerAttackComponent>(atackParamteres);
    input->AddObserver(attackComponent);
}
}  // namespace Roguelike