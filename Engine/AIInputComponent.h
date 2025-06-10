#pragma once
#include "InputComponent.h"
#include "Vector.h"
#include "IObserver.h"
namespace MaxrEngine
{
	class AIInputComponent :
		public InputComponent
	{
	public:
		ENGINE_API AIInputComponent(GameObject* gameObject);

		ENGINE_API void Update(float deltaTime) override;

		ENGINE_API void SetDirection(Vector2Df newDirection);
		ENGINE_API Vector2Df GetDirection() const;
		ENGINE_API void SetAtack(const bool newAtack);
	};
}

