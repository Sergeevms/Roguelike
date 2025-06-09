#pragma once
#include "OpaqueComponent.h"
namespace MaxrEngine
{
	class SpriteOpaqueComponent :
		public OpaqueComponent
	{
	public:
		ENGINE_API SpriteOpaqueComponent(GameObject* gameObject);
		ENGINE_API ~SpriteOpaqueComponent();

		ENGINE_API virtual void Update(float deltaTime) override;
		ENGINE_API virtual void Render() override;
	private:
		const sf::Sprite* sprite;
	};
}

