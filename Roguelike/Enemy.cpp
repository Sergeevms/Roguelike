#include "Enemy.h"

#include "AIAttackComponent.h"
#include "AIBlackboard.h"
#include "AIChaseTargetComponent.h"
#include "AIInputComponent.h"
#include "AIPerceptionComponent.h"
#include "AITargetSelector.h"
#include "ActorComponent.h"
#include "ArmorBarComponent.h"
#include "ArmorComponent.h"
#include "HealthBarComponent.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
#include "PerceptionComponentDebugDraw.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "RigidBodyComponent.h"
#include "Settings.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"

namespace Roguelike {
Enemy::Enemy() : GameObjectContainer("Enemy") {
    auto settings = Settings::Instance();

    auto enemyRender =
        gameObject->AddComponent<MaxrEngine::SpriteRendererComponent>();
    enemyRender->SetTexture(
        *MaxrEngine::ResourceSystem::Instance()->GetTextureShared("Ball"));
    enemyRender->SetPixelSize(settings->playerSize, settings->playerSize);

    auto input = gameObject->AddComponent<MaxrEngine::AIInputComponent>();

    auto enemyMovement =
        gameObject->AddComponent<MaxrEngine::MovementComponent>();
    enemyMovement->SetSpeed(settings->enemySpeed);

    auto body = gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();
    body->SetKinematic(false);

    gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();

    auto enemyChase = gameObject->AddComponent<AIChaseTargetComponent>();
    enemyChase->SetMinimumChaseRadius(settings->enemyChaseMinRadius);
    enemyChase->SetMaximumChaseRadius(settings->enemyChaseMaxRadius);

    gameObject->AddComponent<AIBlackboard>();

    auto perceptionComponent =
        gameObject->AddComponent<AIPerceptionComponent>();
    perceptionComponent->SetSenseRadius(settings->enemySenseRadius);
    perceptionComponent->SetVisionRadius(settings->enemyVisionRadius);
    perceptionComponent->SetVisionAngle(settings->enemyVisionAngle);
    perceptionComponent->SetVisionDirection({-1.f, 0.f});
    input->AddObserver(perceptionComponent);

    auto perceptionDebugDraw =
        gameObject->AddComponent<PerceptionComponentDebugDraw>();

    auto targetSelector = gameObject->AddComponent<AITargetSelector>();

    perceptionComponent->AddObserver(targetSelector);

    auto health =
        gameObject->AddComponent<HealthComponent>(settings->enemyHealth);
    auto healthBar = gameObject->AddComponent<HealthBarComponent>(
        MaxrEngine::Vector2Df(
            0.f, settings->playerSize * 0.5f + settings->healthBarDistance),
        MaxrEngine::Vector2Df(static_cast<float>(settings->playerSize),
                              settings->barHeight),
        settings->barBorder);
    healthBar->SetHealthComponent(health);

    auto armor = gameObject->AddComponent<ArmorComponent>();
    armor->SetDamageReduction(settings->armorDamageReduction * 0.75f);
    armor->SetMaxArmorPoints(settings->enemyHealth);
    armor->SetCurrentArmorPoints(settings->enemyHealth);
    auto armorBar = gameObject->AddComponent<ArmorBarComponent>(
        MaxrEngine::Vector2Df(
            0.f, settings->playerSize * 0.5f + settings->armorBarDistance),
        MaxrEngine::Vector2Df(static_cast<float>(settings->playerSize),
                              settings->barHeight),
        settings->barBorder);
    armorBar->SetArmorComponent(armor);

    auto actorComponent = gameObject->AddComponent<ActorComponent>();
    actorComponent->SetGroupID(ActorsGroups::EnemyGroup);
    auto attackComponent = gameObject->AddComponent<AIAttackComponent>(
        settings->attackCooldown, settings->attackDamage,
        settings->attackRange);
}
}  // namespace Roguelike