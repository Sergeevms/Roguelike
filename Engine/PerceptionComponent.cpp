#include "pch.h"
#include "PerceptionComponent.h"
#include "ActorRegisterSystem.h"
#include "PerceptionSystem.h"

namespace MaxrEngine
{
    PerceptionComponent::PerceptionComponent(GameObject* gameObject)
        : Component(gameObject)
    {
        transform = gameObject->GetComponent<TransformComponent>();
        PerceptionSystem::Instance()->RegisterPerceptionComponent(this);
    }

    PerceptionComponent::~PerceptionComponent()
    {
        PerceptionSystem::Instance()->UnregisterPerceptionComponent(this);
    }

    void PerceptionComponent::Update(float deltaTime)
    {
    }

    void PerceptionComponent::Render()
    {
    }

    void PerceptionComponent::SetVisionAngle(const float newVisionAngle)
    {
        visionAngle = newVisionAngle;
    }

    float PerceptionComponent::GetVisionAngle() const
    {
        return visionAngle;
    }

    void PerceptionComponent::SetVisionRadius(const float newVisionRadius)
    {
        visionRadius = newVisionRadius;
    }

    float PerceptionComponent::GetVisionRadius() const
    {
        return visionRadius;
    }

    void PerceptionComponent::SetSenseRadius(const float newSenseRadius)
    {
        senseRadius = newSenseRadius;
    }

    float PerceptionComponent::GetSenseRadius() const
    {
        return senseRadius;
    }

    void PerceptionComponent::SetVisionDirection(const Vector2Df& newVisionDirection)
    {
        visionDirection = newVisionDirection;
    }

    const Vector2Df& MaxrEngine::PerceptionComponent::GetVisionDirection() const
    {
        return visionDirection;
    }

    const TransformComponent* PerceptionComponent::GetTransform() const
    {
        return transform;
    }

    void PerceptionComponent::UpdateDetectedActors()
    {
        auto& actors = ActorRegisterSystem::Instance()->GetActorsList();
        UpdateDetectedActors(actors);
    }

    void PerceptionComponent::UpdateDetectedActors(const std::vector<GameObject*>& actors)
    {
        detectedActors.clear();
        for (auto& actor : actors)
        {
            if (actor != gameObject && PerceptionSystem::Instance()->CanDetect(this, actor))
            {
                detectedActors.push_back(actor);
            }
        }
        Emit();
    }

    const std::vector<GameObject*>* PerceptionComponent::GetDetectedActors()
    {
        return &detectedActors;
    }
}