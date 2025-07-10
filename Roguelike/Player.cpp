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
#include "HealthBarComponent.h"
#include "ArmorBarComponent.h"

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
		auto healthBar = gameObject->AddComponent<HealthBarComponent>(MaxrEngine::Vector2Df(0.f, settings->playerSize * 0.5f + settings->healthBarDistance),
			MaxrEngine::Vector2Df(static_cast<float>(settings->playerSize), settings->barHeight), settings->barBorder);
		healthBar->SetHealthComponent(health);

		auto armor = gameObject->AddComponent<ArmorComponent>(settings->playerHealth, settings->armorDamageReduction);
		auto armorBar = gameObject->AddComponent<ArmorBarComponent>(MaxrEngine::Vector2Df(0.f, settings->playerSize * 0.5f + settings->armorBarDistance),
			MaxrEngine::Vector2Df(static_cast<float>(settings->playerSize), settings->barHeight), settings->barBorder);
		armorBar->SetArmorComponent(armor);;

		auto actorComponent = gameObject->AddComponent<ActorComponent>();
		actorComponent->SetGroupID(ActorsGroups::PlayerGroup);

		auto atackComponent = gameObject->AddComponent<PlayerAtackComponent>(settings->atackCooldown, settings->atackDamage, settings->atackRange);
		input->AddObserver(atackComponent);
	}
}