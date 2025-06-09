#include "pch.h"
#include "SpriteOpaqueComponent.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"

namespace MaxrEngine
{
	SpriteOpaqueComponent::SpriteOpaqueComponent(GameObject* gameObject)
		: OpaqueComponent(gameObject), sprite(nullptr)
	{
		auto spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
		if (spriteRenderer == nullptr)
		{
			LOG_ERROR("SpriteRendererComponent required to SpriteOpaqueComponent.");
			gameObject->RemoveComponent(this);
			return;
		}

		sprite = spriteRenderer->GetSprite();
		PerceptionSystem::Instance()->RegisterOpaqueComponent(this);
	}

	SpriteOpaqueComponent::~SpriteOpaqueComponent()
	{
		if (&bounds != nullptr)
		{
			std::destroy_at(&bounds);
		}
		PerceptionSystem::Instance()->UnregisterOpaqueComponent(this);
	}

	void SpriteOpaqueComponent::Update(float deltaTime)
	{
		bounds = sprite->getGlobalBounds();
	}

	void SpriteOpaqueComponent::Render()
	{
		OpaqueComponent::Render();
		sf::RectangleShape rectangle(sf::Vector2f(bounds.width, bounds.height));
		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setPosition(bounds.left, bounds.top);
		rectangle.setOutlineColor(sf::Color::Cyan);
		rectangle.setOutlineThickness(-2.f);
		RenderSystem::Instance()->Render(rectangle);
	}
}