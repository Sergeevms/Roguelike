#pragma once
#include "Component.h"
namespace MaxrEngine
{
	class ENGINE_API HealthComponent :
		public Component
	{
	public:
		HealthComponent(GameObject* gameObject);

		virtual void Update(float deltaTime);
		virtual void Render();

		//Set maxHealth & currentHealth to newMaxHealth
		virtual void SetMaxHealth(const int newMaxHealth);
		int GetMaxHealth() const;

		int GetCurrentHealth() const;
		//Decrease health and return overdamage 
		virtual int DecreaseHealth(const int damageAmount);
		//Increase health and return overheal
		virtual int IncreaseHealth(const int healingAmount);
		bool IsAlive() const;
	protected:
		int maxHealth = 0;
		int currentHealth = 0;
	};
}

