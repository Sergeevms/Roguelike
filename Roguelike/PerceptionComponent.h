#pragma once
#include <vector>

#include "Component.h"
#include "IObserver.h"
#include "TransformComponent.h"
#include "Vector.h"
namespace Roguelike {

class PerceptionComponent : public MaxrEngine::Component,
                            public MaxrEngine::IObservable {
   public:
    struct Parameters {
        float visionAngle;
        float visionRadius;
        float visionDirectionX;
        float visionDirectionY;
        float senseRadius;
    };
    static constexpr Parameters defaultParameters = {.visionAngle = 120.0F,
                                                     .visionRadius = 300.0F,
                                                     .visionDirectionX = 1.0F,
                                                     .visionDirectionY = 0.0F,
                                                     .senseRadius = 100.0F};

    explicit PerceptionComponent(
        MaxrEngine::GameObject* gameObject,
        const Parameters& parameters = defaultParameters);
    ~PerceptionComponent();

    void Update(float deltaTime) override;
    void Render() override;

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
    float visionAngle;
    float visionRadius;
    float senseRadius;
    MaxrEngine::Vector2Df visionDirection;
    MaxrEngine::TransformComponent* transform;
    std::vector<MaxrEngine::GameObject*> detectedActors;
};
}  // namespace Roguelike
