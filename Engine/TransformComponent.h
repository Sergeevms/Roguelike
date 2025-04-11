#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Vector.h"
#include "EngineAPI.h"

namespace MaxrEngine
{
	class ENGINE_API TransformComponent :
		public Component
	{
	public:
		TransformComponent(GameObject* gameObject);

		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		void MoveBy(const Vector2Df& offset);
		void RotateBy(const float offset);
		void ScaleBy(const Vector2Df& offset);

		const Vector2Df GetWorldPosition() const;
		const float GetWorldRotation() const;
		const Vector2Df GetWorldScale() const;

	private:
		mutable Vector2Df position = { 0.f, 0.f };
		mutable float rotation = 0.f;
		mutable Vector2Df scale = { 1.f, 1.f };
	};
}

