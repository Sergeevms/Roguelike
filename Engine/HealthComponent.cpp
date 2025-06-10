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

	void MaxrEngine::HealthComponent::SetMaxHealth(const float newMaxHealth)
	{
		assert(newMaxHealth >= 0.f && "maxHealth supposed to be positive");
		if (newMaxHealth < 0.f)
		{
			LOG_WARN("maxHealth supposed to be positive")
		}
		maxHealth = newMaxHealth;
		currentHealth = maxHealth;
	}

	float MaxrEngine::HealthComponent::GetMaxHealth() const
	{
		return maxHealth;
	}

	int HealthComponent::GetCurrentHealth() const
	{
		return currentHealth;
	}

	float MaxrEngine::HealthComponent::DecreaseHealth(const float damageAmount)
	{
		std::ostringstream message;
		message << this << " recieved " << damageAmount << " damage ";
		LOG_INFO(message.str());

		if (currentHealth <= 0.f)
		{
			message.clear();
			message << "Trying to damage " << this << " which has 0.f HP will have no effect";
			LOG_WARN(message.str());
		}

		currentHealth -= damageAmount;
		if (currentHealth < 0.f)
		{
			int overDamage = -currentHealth;
			currentHealth = 0.f;
			return overDamage;
		}
		return 0;
	}

	float MaxrEngine::HealthComponent::IncreaseHealth(const float healingAmount)
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
		return 0.f;
	}

	bool HealthComponent::IsAlive() const
	{
		return currentHealth > 0.f;
	}
}