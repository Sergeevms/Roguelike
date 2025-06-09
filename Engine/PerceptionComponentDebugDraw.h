#pragma once
#include "Component.h"
#include "PerceptionComponent.h"

namespace MaxrEngine
{
	class PerceptionComponentDebugDraw :
		public Component
	{
	public:
		ENGINE_API PerceptionComponentDebugDraw(GameObject* gameObject);

		ENGINE_API virtual void Update(float deltaTime) override;
		ENGINE_API virtual void Render() override;

		ENGINE_API void setArcPointCount(unsigned newArcPointsCount);

	protected:
		std::weak_ptr<PerceptionComponent> perceptionComponent;
		unsigned arcLinesCount = 50;
	};
}