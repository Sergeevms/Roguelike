#include "PerceptionComponent.h"
#include "ActorRegisterSystem.h"
#include "PerceptionSystem.h"

namespace Roguelike
{
    PerceptionComponent::PerceptionComponent(MaxrEngine::GameObject* gameObject)
        : Component(gameObject)
    {
        transform = gameObject->GetComponent<MaxrEngine::TransformComponent>();
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

    void PerceptionComponent::SetVisionDirection(const MaxrEngine::Vector2Df& newVisionDirection)
    {
        if (newVisionDirection.GetLength() > 0.f)
        {
            visionDirection = Normalized(newVisionDirection);
        }
        else
        {
            LOG_WARN("vision direction must not be zero vector");
        }
    }

    const MaxrEngine::Vector2Df& PerceptionComponent::GetVisionDirection() const
    {
        return visionDirection;
    }

    const MaxrEngine::TransformComponent* PerceptionComponent::GetTransform() const
    {
        return transform;
    }

    void PerceptionComponent::UpdateDetectedActors()
    {
        auto& actors = ActorRegisterSystem::Instance()->GetActorsList();
        UpdateDetectedActors(actors);
    }

    void PerceptionComponent::UpdateDetectedActors(const std::vector<MaxrEngine::GameObject*>& actors)
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

    const std::vector<MaxrEngine::GameObject*>* PerceptionComponent::GetDetectedActors()
    {
        return &detectedActors;
    }
}