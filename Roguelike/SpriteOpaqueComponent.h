#pragma once
#include "OpaqueComponent.h"
namespace Roguelike
{
	class SpriteOpaqueComponent :
		public OpaqueComponent
	{
	public:
		SpriteOpaqueComponent(MaxrEngine::GameObject* gameObject);
		~SpriteOpaqueComponent();

		virtual void Update(float deltaTime) override;
		virtual void Render() override;
	private:
		const sf::Sprite* sprite;
	};
}

