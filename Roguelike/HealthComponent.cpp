#include "pch.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include <cassert>
#include "Utility.h"

namespace Roguelike
{
	HealthComponent::HealthComponent(MaxrEngine::GameObject* gameObject, const float maxHealth)
		: Component(gameObject), maxHealth(maxHealth), currentHealth(maxHealth)
	{
	}

	void HealthComponent::Update(float deltaTime)
	{
	}

	void HealthComponent::Render()
	{
	}

	void HealthComponent::SetMaxHealth(const float newMaxHealth)
	{
		assert(newMaxHealth >= 0.f && "maxHealth supposed to be positive");
		if (newMaxHealth < 0.f)
		{
			LOG_WARN("maxHealth supposed to be positive")
		}
		maxHealth = newMaxHealth;
		Emit();
	}

	float HealthComponent::GetMaxHealth() const
	{
		return maxHealth;
	}

	void HealthComponent::SetCurrentHealth(const float newCurrentHealth)
	{
		if (InRange(newCurrentHealth, 0.f, maxHealth))
		{
			currentHealth = newCurrentHealth;
			Emit();
		}		
	}

	float Roguelike::HealthComponent::GetCurrentHealth() const
	{
		return currentHealth;
	}

	float HealthComponent::DecreaseHealth(const float damageAmount)
	{
		std::ostringstream message;
		message << this << " recieved " << damageAmount << " damage ";
		LOG_INFO(message.str());

		if (currentHealth <= 0.f)
		{
			message.clear();
			message << "Trying to damage " << this << " which has 0.f HP will have no effect";
			LOG_WARN(message.str());
			return damageAmount;
		}

		currentHealth -= damageAmount;
		if (currentHealth < 0.f)
		{
			float overDamage = -currentHealth;
			currentHealth = 0.f;
			Emit();
			return overDamage;
		}
		Emit();
		return 0;
	}

	float HealthComponent::IncreaseHealth(const float healingAmount)
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
			return healingAmount;
		}

		currentHealth += healingAmount;
		if (currentHealth > maxHealth)
		{
			float overHeal = currentHealth - maxHealth;
			currentHealth = maxHealth;
			message << "Healing " << overHeal << " health points not applied due to going over maxHealth";
			LOG_INFO(message.str());
			message.clear();
			Emit();
			return overHeal;
		}
		Emit();
		return 0.f;
	}

	bool HealthComponent::IsAlive() const
	{
		return currentHealth > 0.f;
	}
}