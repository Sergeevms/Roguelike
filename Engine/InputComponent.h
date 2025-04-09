#pragma once
#include "Component.h"
namespace MaxrEngine
{
	class InputComponent :
		public Component
	{
	public:
		InputComponent(GameObject* gameObject);

		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		float GetHorizontalAxis() const;
		float GetVerticalAxis() const;
	private:
		float horizontalAxis = 0.f;
		float verticalAxis = 0.f;
	};
}

