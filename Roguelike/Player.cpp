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
#include "Settings.h"

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

		auto playerInput = gameObject->AddComponent<MaxrEngine::InputComponent>();

		auto playerMovement = gameObject->AddComponent<MaxrEngine::MovementComponent>();
		playerMovement->SetSpeed(settings->playerSpeed);

		auto transform = gameObject->GetComponent<MaxrEngine::TransformComponent>();

		auto body = gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();
		body->SetKinematic(false);

		auto collider = gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();
	}
}