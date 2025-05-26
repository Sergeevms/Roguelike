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
#include "AITargetSearchComponent.h"
#include "AIChaseTargetComponent.h"
#include "HealthComponent.h"
#include "ArmorComponent.h"

namespace Roguelike
{
	Enemy::Enemy() :
		GameObjectContainer("Enemy")
	{
		auto settings = Settings::Instance();

		auto enemyRender = gameObject->AddComponent<MaxrEngine::SpriteRendererComponent>();
		enemyRender->SetTexture(*MaxrEngine::ResourceSystem::Instance()->GetTextureShared("Ball"));
		enemyRender->SetPixelSize(settings->playerSize, settings->playerSize);

		gameObject->AddComponent<MaxrEngine::AIInputComponent>();

		auto enemyMovement = gameObject->AddComponent<MaxrEngine::MovementComponent>();
		enemyMovement->SetSpeed(settings->playerSpeed * 0.5f);
		
		auto body = gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();
		body->SetKinematic(false);

		gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();
		auto enemyChase = gameObject->AddComponent<AIChaseTargetComponent>();
		enemyChase->SetMinimumChaseRadius(settings->enemyChaseMinRadius);
		enemyChase->SetMaximumChaseRadius(settings->enemyChaseMaxRadius);

		gameObject->AddComponent<AIBlackboard>();

		auto enemyTarget = gameObject->AddComponent<AITargetSearchComponent>();
		enemyTarget->SetDetectionRange(settings->enemyDetectionRadius);

		auto health = gameObject->AddComponent<MaxrEngine::HealthComponent>();
		health->SetMaxHealth(settings->enemyHealth);

		auto armor = gameObject->AddComponent<MaxrEngine::ArmorComponent>();
		armor->SetDamageReduction(settings->armorDamageReduction);
		armor->SetMaxArmorPoints(settings->enemyHealth);
	}
}