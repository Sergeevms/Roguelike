#include "Floor.h"
#include "GameWorld.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "ResourceSystem.h"
#include "Settings.h"

namespace Roguelike
{
	Floor::Floor(MaxrEngine::Vector2Df position, int textureIndex, MaxrEngine::Vector2Di size) :
		GameObjectContainer("Floor")
	{
		auto settings = Settings::Instance();

		auto transform = gameObject->GetComponent<MaxrEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto sprite = gameObject->AddComponent<MaxrEngine::SpriteRendererComponent>();
		sprite->SetTexture(*MaxrEngine::ResourceSystem::Instance()->GetTextureMapElementShared("FloorTextures", textureIndex));
		sprite->SetPixelSize(size.x, size.y);
	}
}