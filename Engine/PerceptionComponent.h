#pragma once
#include "Component.h"
#include "Vector.h"
#include "TransformComponent.h"
namespace MaxrEngine
{
	class PerceptionComponent :
		public Component
	{
	public:
		ENGINE_API PerceptionComponent(GameObject* gameObject);
		ENGINE_API ~PerceptionComponent();

		ENGINE_API virtual void Update(float deltaTime) override;
		ENGINE_API virtual void Render() override;

		ENGINE_API void SetVisionAngle(const float newVisionAngle);
		ENGINE_API float GetVisionAngle() const;

		ENGINE_API void SetVisionRadius(const float newVisionRadius);
		ENGINE_API float GetVisionRadius() const;

		ENGINE_API void SetSenseRadius(const float newSenseRadius);
		ENGINE_API float GetSenseRadius() const;

		ENGINE_API void SetVisionDirection(const Vector2Df& newVisionDirection);
		ENGINE_API const Vector2Df& GetVisionDirection() const;

		ENGINE_API const TransformComponent* GetTransform() const;

		ENGINE_API void UpdateDetectedActors();
		ENGINE_API void UpdateDetectedActors(const std::vector<GameObject*>& actors);
		ENGINE_API const std::vector<GameObject*>* GetDetectedActors();
		
	protected:
		float visionAngle = 360.f;
		float visionRadius = 300.f;
		float senseRadius = 100.f;
		Vector2Df visionDirection = { 1.f, 0.f };
		TransformComponent* transform;
		std::vector<GameObject*> detectedActors;
	};
}

