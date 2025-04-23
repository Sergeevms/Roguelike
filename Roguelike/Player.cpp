#include "Player.h"
#include "ResourceSystem.h"
#include "RenderSystem.h"
#include "..\Engine\GameWorld.h"
#include "SpriteRendererComponent.h"
#include "CameraComponent.h"
#include "InputComponent.h"
#include "SpriteColliderComponent.h"

namespace Roguelike
{
	Player::Player()
	{
		gameObject = MaxrEngine::GameWorld::Instance()->CreateGameObject();

		auto playerRender = gameObject->AddComponent<MaxrEngine::SpriteRendererComponent>();
		playerRender->SetTexture(*MaxrEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
		playerRender->SetPixelSize(32, 32);

		auto playerCamera = gameObject->AddComponent<MaxrEngine::CameraComponent>();
		playerCamera->SetWindow(&MaxrEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(1280, 720);

		auto playerInput = gameObject->AddComponent<MaxrEngine::InputComponent>();

		auto transform = gameObject->GetComponent<MaxrEngine::TransformComponent>();

		auto collider = gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();
	}

	MaxrEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}