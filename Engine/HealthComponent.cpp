#include "pch.h"
#include "HealthComponent.h"
#include <cassert>

namespace MaxrEngine
{
	HealthComponent::HealthComponent(GameObject* gameObject)
		: Component(gameObject)
	{
	}

	void HealthComponent::Update(float deltaTime)
	{
	}

	void HealthComponent::Render()
	{
	}

	void HealthComponent::SetMaxHealth(const int newMaxHealth)
	{
		assert(newMaxHealth >= 0 && "maxHealth supposed to be positive");
		if (newMaxHealth < 0)
		{
			LOG_WARN("maxHealth supposed to be positive")
		}
		maxHealth = newMaxHealth;
		currentHealth = maxHealth;
	}

	int HealthComponent::GetMaxHealth() const
	{
		return maxHealth;
	}

	int HealthComponent::GetCurrentHealth() const
	{
		return currentHealth;
	}

	int HealthComponent::DecreaseHealth(const int damageAmount)
	{
		std::ostringstream message;
		message << this << " recieved " << damageAmount << " damage ";
		LOG_INFO(message.str());

		if (currentHealth <= 0)
		{
			message.clear();
			message << "Trying to damage " << this << " which has 0 HP will have no effect";
			LOG_WARN(message.str());
		}

		currentHealth -= damageAmount;
		if (currentHealth < 0)
		{
			int overDamage = -currentHealth;
			currentHealth = 0;
			return overDamage;
		}
		return 0;
	}

	int HealthComponent::IncreaseHealth(const int healingAmount)
	{
		std::ostringstream message;
		message << this << " recieved " << healingAmount << " healing ";
		LOG_INFO(message.str());
		message.clear();

		if (currentHealth >= maxHealth)
		{
			message << "Trying to heal " << this << " which has maximum HP will have no effect";
			LOG_WARN(message.str());
			message.clear();
		}

		currentHealth += healingAmount;
		if (currentHealth > maxHealth)
		{
			int overHeal = currentHealth - maxHealth;
			currentHealth = maxHealth;
			message << "Healing " << overHeal << " health points not applied due to going over maxHealth";
			LOG_INFO(message.str());
			message.clear();
			return overHeal;
		}
		return 0;
	}

	bool HealthComponent::IsAlive() const
	{
		return currentHealth > 0;
	}
}