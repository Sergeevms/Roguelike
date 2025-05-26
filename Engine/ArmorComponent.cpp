#include "pch.h"
#include "ArmorComponent.h"
#include <cassert>

namespace MaxrEngine
{
	ArmorComponent::ArmorComponent(GameObject* gameObject)
		: Component(gameObject)
	{
	}

	void ArmorComponent::Update(float deltaTime)
	{
	}

	void ArmorComponent::Render()
	{
	}

	void ArmorComponent::SetMaxArmorPoints(const int newMaxArmorPoints)
	{
		assert(newMaxArmorPoints >= 0 && "maxArmorPoints supposed to be positive");
		if (newMaxArmorPoints < 0)
		{
			LOG_WARN("maxArmorPoints supposed to be positive - setted to 0");
			maxArmorPoints = 0;
			return;
		}
		maxArmorPoints = newMaxArmorPoints;
	}

	int ArmorComponent::GetMaxArmorPoints() const
	{
		return maxArmorPoints;
	}

	void ArmorComponent::SetDamageReduction(const float newDamageReduction)
	{
		assert((newDamageReduction >= 0.f && newDamageReduction <= 1.f) && "newDamageReduction supposed to be in range 0.f - 1.f");
		if (newDamageReduction < 0.f || newDamageReduction > 1.f)
		{
			LOG_WARN("newDamageReduction supposed to be in range 0.f - 1.f. Setted to 1.f");
			damageReduction = 1.f;
			return;
		}
		damageReduction = newDamageReduction;
	}

	int ArmorComponent::GetCurrentArmorPoints() const
	{
		return currentArmorPoints;
	}

	int ArmorComponent::ApplyDamage(const int damageAmount)
	{
		std::ostringstream message;

		if (currentArmorPoints <= 0)
		{
			message << "Trying to damage " << this << " which has 0 armorPoints will have no effect";
			LOG_WARN(message.str());
			message.clear();
		}

		int absorbedDamage = std::min(currentArmorPoints, static_cast<int>(damageAmount * damageReduction));
		message << this << " recieved " << damageAmount << " damage - " << absorbedDamage << " absorbed";
		LOG_INFO(message.str());
		currentArmorPoints -= absorbedDamage;
		return damageAmount - absorbedDamage > 0 ? damageAmount - absorbedDamage : 0;
	}

	int ArmorComponent::IncreaseArmorPoints(const int armorPointAmount)
	{
		std::ostringstream message;
		message << this << " recieved " << armorPointAmount << " armorPoints ";
		LOG_INFO(message.str());
		message.clear();

		if (currentArmorPoints >= maxArmorPoints)
		{
			message << "Trying to restore armor " << this << " which has maximum ArmorPoints will have no effect";
			LOG_WARN(message.str());
			message.clear();
		}

		currentArmorPoints += armorPointAmount;
		if (currentArmorPoints > currentArmorPoints)
		{
			int overArmorRestore = currentArmorPoints - maxArmorPoints;
			currentArmorPoints = maxArmorPoints;
			message << "Restoring " << overArmorRestore << " not applied due to going over maxArmorPoints";
			LOG_INFO(message.str());
			message.clear();
			return overArmorRestore;
		}
		return 0;
	}
	bool ArmorComponent::IsNotBroken() const
	{
		return currentArmorPoints > 0;
	}
}
