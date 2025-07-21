#include "Enemy.h"

#include "SFML/Graphics/Color.hpp"

#include "AIAttackComponent.h"
#include "AIBlackboard.h"
#include "AIChaseTargetComponent.h"
#include "AIInputComponent.h"
#include "AIPerceptionComponent.h"
#include "AITargetSelector.h"
#include "ActorComponent.h"
#include "ArmorBarComponent.h"
#include "ArmorComponent.h"
#include "AttackComponent.h"
#include "BarComponent.h"
#include "GameObjectContainer.h"
#include "HealthBarComponent.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
#include "PerceptionComponentDebugDraw.h"
#include "ResourceSystem.h"
#include "RigidBodyComponent.h"
#include "Settings.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"
#include "Utility.h"
#include "Vector.h"

namespace Roguelike {
Enemy::Enemy() : GameObjectContainer("Enemy") {
    auto* settings = Settings::Instance();

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
    const MaxrEngine::Vector2Df leftDirection = {-1.0F, 0.0F};
    perceptionComponent->SetVisionDirection(leftDirection);
    input->AddObserver(perceptionComponent);

    auto perceptionDebugDraw =
        gameObject->AddComponent<PerceptionComponentDebugDraw>();

    auto targetSelector = gameObject->AddComponent<AITargetSelector>();

    perceptionComponent->AddObserver(targetSelector);

    auto health =
        gameObject->AddComponent<HealthComponent>(settings->enemyHealth);
    const BarComponent::BarComponentParameters healthBarParameters{
        .centerOffset = {0.0F, Half(settings->PlayerSizeF()) +
                                   settings->healthBarDistance},
        .barSize =
            MaxrEngine::Vector2Df(settings->PlayerSizeF(), settings->barHeight),
        .barColor = sf::Color::Red,
        .borderSize = settings->barBorder};
    auto healthBar =
        gameObject->AddComponent<HealthBarComponent>(healthBarParameters);
    healthBar->SetHealthComponent(health);

    auto armor = gameObject->AddComponent<ArmorComponent>();
    const float enemyAramorDamageReduction =
        settings->armorDamageReduction * 0.75F;
    armor->SetDamageReduction(enemyAramorDamageReduction);
    armor->SetMaxArmorPoints(settings->enemyHealth);
    armor->SetCurrentArmorPoints(settings->enemyHealth);
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

    auto actorComponent = gameObject->AddComponent<ActorComponent>();
    actorComponent->SetGroupID(ActorsGroups::EnemyGroup);
    const AttackComponent::AtackComponentParameters atackParamteres{
        .cooldown = settings->attackCooldown,
        .damage = settings->attackDamage,
        .range = settings->attackRange};
    auto attackComponent =
        gameObject->AddComponent<AIAttackComponent>(atackParamteres);
}
}  // namespace Roguelike