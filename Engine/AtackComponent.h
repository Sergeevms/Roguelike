#pragma once
#include "Component.h"
#include "IObserver.h"
namespace MaxrEngine
{
	class ENGINE_API AtackComponent :
		public Component, public IObserver
	{
	public:
		AtackComponent(GameObject* gameObject, float cooldown = 0.f, float damage = 0.f, float range = 0.f, GameObject* tartget = nullptr);

		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		void SetCooldown(const float newCoolDown);
		float GetCooldwon() const;

		void SetDamage(const float newDamage);
		float GetDamage() const;

		void SetRange(const float newRange);
		float GetRange() const;

		void SetTarget(GameObject * newTarget);
		GameObject* GetTarget() const;

		void Notify(std::shared_ptr<IObservable> observable) override;

	protected:
		GameObject* target;
		float currentCooldown;
		float cooldown;
		float damage;
		float range;
	};
}

