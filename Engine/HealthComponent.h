#pragma once
#include "Component.h"
namespace MaxrEngine
{
	class ENGINE_API HealthComponent :
		public Component
	{
	public:
		HealthComponent(GameObject* gameObject);

		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		//Set maxHealth & currentHealth to newMaxHealth
		virtual void SetMaxHealth(const float newMaxHealth);
		float GetMaxHealth() const;

		int GetCurrentHealth() const;
		//Decrease health and return overdamage 
		virtual float DecreaseHealth(const float damageAmount);
		//Increase health and return overheal
		virtual float IncreaseHealth(const float healingAmount);
		bool IsAlive() const;
	protected:
		float maxHealth = 0.f;
		float currentHealth = 0.f;
	};
}

