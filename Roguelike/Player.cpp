#include "Player.h"

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
    auto healthBar = gameObject->AddComponent<HealthBarComponent>(
        settings->healthBarParameters);
    healthBar->SetHealthComponent(health);

    const ArmorComponent::ArmorComponentParameters armorParameters = {
        .maxArmorPoints = settings->playerHealth,
        .damageReduction = settings->armorDamageReduction};
    auto armor = gameObject->AddComponent<ArmorComponent>(armorParameters);
    auto armorBar = gameObject->AddComponent<ArmorBarComponent>(
        settings->armorBarParameters);
    armorBar->SetArmorComponent(armor);
    ;

    auto actorComponent = gameObject->AddComponent<ActorComponent>();
    actorComponent->SetGroupID(ActorsGroups::PlayerGroup);

    auto attackComponent = gameObject->AddComponent<PlayerAttackComponent>(
        settings->playerAtackParameters);
    input->AddObserver(attackComponent);

    auto blockComponent = gameObject->AddComponent<BlockComponent>(
        settings->playerBlockParameters);
}
}  // namespace Roguelike