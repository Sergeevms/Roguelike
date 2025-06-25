#include "Player.h"
#include "ResourceSystem.h"
#include "RenderSystem.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "CameraComponent.h"
#include "InputComponent.h"
#include "SpriteColliderComponent.h"
#include "RigidBodyComponent.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
#include "ArmorComponent.h"
#include "KeyboardInputComponent.h"
#include "Settings.h"
#include "ActorComponent.h"
#include "PlayerAtackComponent.h"

namespace Roguelike
{
	Player::Player() :
		GameObjectContainer("Player")
	{
		auto settings = Settings::Instance();

		auto playerRender = gameObject->AddComponent<MaxrEngine::SpriteRendererComponent>();
		playerRender->SetTexture(*MaxrEngine::ResourceSystem::Instance()->GetTextureMapElementShared("PlayerTextures", 0));
		playerRender->SetPixelSize(settings->playerSize, settings->playerSize);

		auto playerCamera = gameObject->AddComponent<MaxrEngine::CameraComponent>();
		playerCamera->SetWindow(&MaxrEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(settings->screenWidth, settings->screenHeight);

		auto input = gameObject->AddComponent<MaxrEngine::KeyboardInputComponent>();

		auto playerMovement = gameObject->AddComponent<MaxrEngine::MovementComponent>();
		playerMovement->SetSpeed(settings->playerSpeed);

		auto body = gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();
		body->SetKinematic(false);

		gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();

		auto health = gameObject->AddComponent<HealthComponent>(settings->playerHealth);

		auto armor = gameObject->AddComponent<ArmorComponent>(settings->playerHealth, settings->armorDamageReduction);

		auto actorComponent = gameObject->AddComponent<ActorComponent>();
		actorComponent->SetGroupID(ActorsGroups::PlayerGroup);

		auto atackComponent = gameObject->AddComponent<PlayerAtackComponent>(settings->atackCooldown, settings->atackDamage, settings->atackRange);
		input->AddObserver(atackComponent);
	}
}