#pragma once
#include "InputComponent.h"
#include "Vector.h"
namespace MaxrEngine
{
	class AIInputComponent :
		public InputComponent
	{
	public:
		ENGINE_API AIInputComponent(GameObject* gameObject);

		ENGINE_API void Update(float deltaTime) override;

		ENGINE_API void SetDirection(Vector2Df direction);
	};
}

