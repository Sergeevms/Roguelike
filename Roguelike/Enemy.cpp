#include "Enemy.h"
#include "Settings.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"
#include "RigidBodyComponent.h"
#include "RenderSystem.h"
#include "AIInputComponent.h"
#include "MovementComponent.h"
#include "SpriteRendererComponent.h"
#include "AIBlackboard.h"
#include "AITargetSelector.h"
#include "AIChaseTargetComponent.h"
#include "HealthComponent.h"
#include "ArmorComponent.h"
#include "ActorComponent.h"
#include "AIPerceptionComponent.h"
#include "PerceptionComponentDebugDraw.h"

namespace Roguelike
{
	Enemy::Enemy() :
		GameObjectContainer("Enemy")
	{
		auto settings = Settings::Instance();

		auto enemyRender = gameObject->AddComponent<MaxrEngine::SpriteRendererComponent>();
		enemyRender->SetTexture(*MaxrEngine::ResourceSystem::Instance()->GetTextureShared("Ball"));
		enemyRender->SetPixelSize(settings->playerSize, settings->playerSize);

		auto input = gameObject->AddComponent<MaxrEngine::AIInputComponent>();

		auto enemyMovement = gameObject->AddComponent<MaxrEngine::MovementComponent>();
		enemyMovement->SetSpeed(settings->enemySpeed);
		
		auto body = gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();
		body->SetKinematic(false);

		gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();

		auto enemyChase = gameObject->AddComponent<AIChaseTargetComponent>();
		enemyChase->SetMinimumChaseRadius(settings->enemyChaseMinRadius);
		enemyChase->SetMaximumChaseRadius(settings->enemyChaseMaxRadius);

		gameObject->AddComponent<AIBlackboard>();

		auto perceptionComponent = gameObject->AddComponent<AIPerceptionComponent>();
		perceptionComponent->SetSenseRadius(settings->enemySenseRadius);
		perceptionComponent->SetVisionRadius(settings->enemyVisionRadius);
		perceptionComponent->SetVisionAngle(settings->enemyVisionAngle);
		perceptionComponent->SetVisionDirection({ -1.f, 0.f });
		input->AddObserver(perceptionComponent);

		auto perceptionDebugDraw = gameObject->AddComponent<MaxrEngine::PerceptionComponentDebugDraw>();

		auto targetSelector = gameObject->AddComponent<AITargetSelector>();

		perceptionComponent->AddObserver(targetSelector);
		
		auto health = gameObject->AddComponent<MaxrEngine::HealthComponent>();
		health->SetMaxHealth(settings->enemyHealth);

		auto armor = gameObject->AddComponent<MaxrEngine::ArmorComponent>();
		armor->SetDamageReduction(settings->armorDamageReduction);
		armor->SetMaxArmorPoints(settings->enemyHealth);

		auto actorComponent = gameObject->AddComponent<MaxrEngine::ActorComponent>();
		actorComponent->SetGroupID(ActorsGroups::EnemyGroup);		
	}
}