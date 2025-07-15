#pragma once
#include "Component.h"
#include "IObserver.h"
namespace Roguelike
{
	class AttackComponent :
		public MaxrEngine::Component
	{
	public:
		AttackComponent(MaxrEngine::GameObject* gameObject, float cooldown = 0.f, float damage = 0.f, float range = 0.f,
			std::weak_ptr<MaxrEngine::GameObject> target = std::weak_ptr<MaxrEngine::GameObject>());

		virtual void Update(float deltaTime) override;
		virtual void Render() override;
		
		virtual void Attack();

		void SetCooldown(const float newCoolDown);
		float GetCooldwon() const;

		void SetDamage(const float newDamage);
		float GetDamage() const;

		void SetRange(const float newRange);
		float GetRange() const;

		void SetTarget(std::weak_ptr<MaxrEngine::GameObject> newTarget);
		std::shared_ptr<MaxrEngine::GameObject> GetTarget() const;

	protected:
		std::weak_ptr<MaxrEngine::GameObject> target;
		float currentCooldown;
		float cooldown;
		float damage;
		float range;
	};
}

