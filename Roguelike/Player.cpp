#include "Player.h"
#include "ResourceSystem.h"
#include "RenderSystem.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "CameraComponent.h"
#include "InputComponent.h"
#include "SpriteColliderComponent.h"
#include "RigidBodyComponent.h"
#include "Settings.h"

namespace Roguelike
{
	Player::Player()
	{
		auto settings = Settings::Instance();
		gameObject = MaxrEngine::GameWorld::Instance()->CreateGameObject("Player");

		auto playerRender = gameObject->AddComponent<MaxrEngine::SpriteRendererComponent>();
		playerRender->SetTexture(*MaxrEngine::ResourceSystem::Instance()->GetTextureMapElementShared("PlayerTextures", 0));
		playerRender->SetPixelSize(settings->playerSize, settings->playerSize);

		auto playerCamera = gameObject->AddComponent<MaxrEngine::CameraComponent>();
		playerCamera->SetWindow(&MaxrEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(1280, 720);

		auto playerInput = gameObject->AddComponent<MaxrEngine::InputComponent>();

		auto transform = gameObject->GetComponent<MaxrEngine::TransformComponent>();

		auto body = gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();

		auto collider = gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();
	}

	MaxrEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}