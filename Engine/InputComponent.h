#pragma once
#include "Component.h"
#include "EngineAPI.h"

namespace MaxrEngine
{
	class ENGINE_API InputComponent :
		public Component
	{
	public:
		InputComponent(GameObject* gameObject);

		virtual void Update(float deltaTime) = 0;
		virtual void Render() override;

		float GetHorizontalAxis() const;
		float GetVerticalAxis() const;
	protected:
		float horizontalAxis = 0.f;
		float verticalAxis = 0.f;
	};
}

