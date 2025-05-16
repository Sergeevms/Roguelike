#pragma once
#include "InputComponent.h"
namespace MaxrEngine
{
	class ENGINE_API KeyboardInputComponent :
		public InputComponent
	{
	public:
		KeyboardInputComponent(GameObject* gameObject);

		virtual void Update(float deltaTime) override;
	};
}

