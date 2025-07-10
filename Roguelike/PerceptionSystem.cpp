#include "PerceptionSystem.h"
#include "OpaqueComponent.h"
#include "PerceptionComponent.h"
#include "ActorRegisterSystem.h"
#include <limits>

namespace Roguelike
{
	PerceptionSystem* PerceptionSystem::Instance()
	{
		static PerceptionSystem instance;
		return &instance;
	}

	void PerceptionSystem::Update()
	{
		auto& actors = ActorRegisterSystem::Instance()->GetActorsList();
		for (auto& component : perceptionComponents)
		{
			component->UpdateDetectedActors(actors);
		}
	}

	bool PerceptionSystem::CanDetect(PerceptionComponent* perceptionComponent, MaxrEngine::GameObject* target) const
	{
		auto& perceptionPosition = perceptionComponent->GetTransform()->GetWorldPosition();
		auto& targetPosition = target->GetComponent<MaxrEngine::TransformComponent>()->GetWorldPosition();
		MaxrEngine::Vector2Df betweenVector = targetPosition - perceptionPosition;
		float distance = betweenVector.GetLength();
		if (distance <= perceptionComponent->GetSenseRadius())
		{
			return true;
		}
		if (distance > perceptionComponent->GetVisionRadius())
		{
			return false;
		}
		else
		{
			float angle = AngleDegree(perceptionComponent->GetVisionDirection(), betweenVector);
			if (angle > perceptionComponent->GetVisionAngle() / 2.f)
			{
				return false;
			}
			return LineClear(perceptionPosition, targetPosition);
		}
	}

	bool PerceptionSystem::LineClear(const MaxrEngine::Vector2Df& startPoint, const MaxrEngine::Vector2Df& endPoint) const
	{
		auto direction = endPoint - startPoint;
		auto directionLength = direction.GetLength();
		direction = MaxrEngine::Normalized(direction);
		float invDirX = 1.f / direction.x;
		bool positiveX = invDirX >= 0.f;
		float invDirY = 1.f / direction.y;
		bool positiveY = invDirY >= 0.f;

		for (auto& opaque : opaqueComponents)
		{
			float tMin = 0.f;
			float tMax = directionLength;
			float tMinX = ((positiveX ? opaque->bounds.left : opaque->bounds.left + opaque->bounds.width) - startPoint.x) * invDirX;
			float tMaxX = ((positiveX ? opaque->bounds.left + opaque->bounds.width : opaque->bounds.left) - startPoint.x) * invDirX;
			if (tMin > tMaxX || tMax < tMinX)
			{
				continue;
			}
			tMin = std::max(tMin, tMinX);
			tMax = std::min(tMax, tMaxX);
			float tMinY = ((positiveY ? opaque->bounds.top : opaque->bounds.top + opaque->bounds.height) - startPoint.y) * invDirY;
			float tMaxY = ((positiveY ? opaque->bounds.top + opaque->bounds.height : opaque->bounds.top) - startPoint.y) * invDirY;
			if (tMin > tMaxY || tMax < tMinY)
			{
				continue;
			}
			return false;
		}
		return true;
	}

	void PerceptionSystem::RegisterOpaqueComponent(OpaqueComponent* component)
	{
		opaqueComponents.push_back(component);
	}

	void PerceptionSystem::UnregisterOpaqueComponent(OpaqueComponent* component)
	{
		opaqueComponents.erase(std::remove_if(opaqueComponents.begin(), opaqueComponents.end(),
			[component](OpaqueComponent* comp) { return component == comp; }));
	}

	void PerceptionSystem::RegisterPerceptionComponent(PerceptionComponent* component)
	{
		perceptionComponents.push_back(component);
	}

	void PerceptionSystem::UnregisterPerceptionComponent(PerceptionComponent* component)
	{
		perceptionComponents.erase(std::remove_if(perceptionComponents.begin(), perceptionComponents.end(),
			[component](PerceptionComponent* comp) { return component == comp; }));
	}

	void PerceptionSystem::ClearOpaqueObjects()
	{
		opaqueComponents.clear();
	}

	void PerceptionSystem::ClearPerceptionComponents()
	{
		perceptionComponents.clear();
	}

	void PerceptionSystem::Clear()
	{
		ClearOpaqueObjects();
		ClearPerceptionComponents();
	}
}