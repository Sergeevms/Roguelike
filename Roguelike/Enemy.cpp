#include "Enemy.h"
#include "Settings.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"
#include "RigidBodyComponent.h"
#include "RenderSystem.h"
#include "AIInputComponent.h"
#include "MovementComponent.h"
#include "SpriteRendererComponent.h"

namespace Roguelike
{
	Enemy::Enemy() :
		GameObjectContainer("Enemy")
	{
		auto settings = Settings::Instance();

		auto enemyRender = gameObject->AddComponent<MaxrEngine::SpriteRendererComponent>();
		enemyRender->SetTexture(*MaxrEngine::ResourceSystem::Instance()->GetTextureShared("Ball"));
		enemyRender->SetPixelSize(settings->playerSize, settings->playerSize);

		auto enemyInput = gameObject->AddComponent<MaxrEngine::AIInputComponent>();

		auto enemyMovement = gameObject->AddComponent<MaxrEngine::MovementComponent>();
		enemyMovement->SetSpeed(settings->playerSpeed * 0.7f);

		auto transform = gameObject->GetComponent<MaxrEngine::TransformComponent>();
		transform->MoveBy({ settings->playerSize * 10.f, settings->playerSize * 8.f });

		auto body = gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();
		body->SetKinematic(false);

		auto collider = gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();
	}
}