#pragma once
#include "Component.h"
#include "IObserver.h"
#include "TransformComponent.h"
#include "Vector.h"
namespace Roguelike {
class PerceptionComponent : public MaxrEngine::Component,
                            public MaxrEngine::IObservable {
   public:
    PerceptionComponent(MaxrEngine::GameObject* gameObject);
    ~PerceptionComponent();

    virtual void Update(float deltaTime) override;
    virtual void Render() override;

    void SetVisionAngle(const float newVisionAngle);
    float GetVisionAngle() const;

    void SetVisionRadius(const float newVisionRadius);
    float GetVisionRadius() const;

    void SetSenseRadius(const float newSenseRadius);
    float GetSenseRadius() const;

    void SetVisionDirection(const MaxrEngine::Vector2Df& newVisionDirection);
    const MaxrEngine::Vector2Df& GetVisionDirection() const;

    const MaxrEngine::TransformComponent* GetTransform() const;

    void UpdateDetectedActors();
    void UpdateDetectedActors(
        const std::vector<MaxrEngine::GameObject*>& actors);
    const std::vector<MaxrEngine::GameObject*>* GetDetectedActors();

   protected:
    float visionAngle = 360.f;
    float visionRadius = 300.f;
    float senseRadius = 100.f;
    MaxrEngine::Vector2Df visionDirection = {1.f, 0.f};
    MaxrEngine::TransformComponent* transform;
    std::vector<MaxrEngine::GameObject*> detectedActors;
};
}  // namespace Roguelike
