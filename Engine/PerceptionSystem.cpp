#include "pch.h"
#include "PerceptionSystem.h"
#include "OpaqueComponent.h"
#include "PerceptionComponent.h"
#include "ActorRegisterSystem.h"
#include <limits>

namespace MaxrEngine
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

	bool PerceptionSystem::CanDetect(PerceptionComponent* perception, GameObject* target) const
	{
		auto perceptionPosition = perception->GetTransform()->GetWorldPosition();
		auto targetPosition = target->GetComponent<TransformComponent>()->GetWorldPosition();
		Vector2Df betweenVector = targetPosition - perceptionPosition;
		float distance = betweenVector.GetLength();
		if (distance <= perception->GetSenseRadius())
		{
			return true;
		}
		if (distance > perception->GetVisionRadius())
		{
			return false;
		}
		else
		{
			float angle = AngleDegree(perception->GetVisionDirection(), betweenVector);
			if (angle > perception->GetVisionAngle() / 2.f)
			{
				return false;
			}
			return LineClear(perceptionPosition, targetPosition);
		}
	}

	bool MaxrEngine::PerceptionSystem::LineClear(const Vector2Df& startPoint, const Vector2Df& endPoint) const
	{
		auto direction = endPoint - startPoint;
		bool parallelToXAxis = std::abs(direction.x) < std::numeric_limits<float>::epsilon();
		float invDirX = parallelToXAxis ? std::numeric_limits<float>::infinity() : 1.f / direction.x;
		bool parallelToYAxis = std::abs(direction.y) < std::numeric_limits<float>::epsilon();
		float invDirY = parallelToYAxis ? std::numeric_limits<float>::infinity() : 1.f / direction.y;

		for (auto& opacque : opaqueComponents)
		{
			float tMin = 0.f;
			float tMax = std::numeric_limits<float>::max();

			if (parallelToXAxis)
			{
				if (startPoint.x < opacque->bounds.left || startPoint.x > opacque->bounds.left + opacque->bounds.width)
				{
					continue;
				}
			}
			else
			{
				float t1 = (opacque->bounds.left - startPoint.x) * invDirX;
				float t2 = (opacque->bounds.left + opacque->bounds.width - startPoint.x) * invDirX;

				tMin = std::max(tMin, std::min(t1, t2));
				tMax = std::min(tMax, std::max(t1, t2));

				if (tMax < tMin)
				{
					continue;
				}
			}

			if (parallelToYAxis)
			{
				if (startPoint.y < opacque->bounds.top || startPoint.y > opacque->bounds.top + opacque->bounds.height)
				{
					continue;
				}
			}
			else
			{			
				float t1 = (opacque->bounds.top - startPoint.x) * invDirX;
				float t2 = (opacque->bounds.top + opacque->bounds.height - startPoint.x) * invDirX;

				tMin = std::max(tMin, std::min(t1, t2));
				tMax = std::min(tMax, std::max(t1, t2));

				if (tMax < tMin)
				{
					continue;
				}			
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