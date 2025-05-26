#pragma once
#include "Component.h"
namespace MaxrEngine
{
	class ENGINE_API ArmorComponent :
		public Component
	{
	public:
		ArmorComponent(GameObject* gameObject);

		virtual void Update(float deltaTime);
		virtual void Render();

		virtual void SetMaxArmorPoints(const int newMaxArmorPoints);
		int GetMaxArmorPoints() const;

		//Sets damage reduction in 0.f - 1.f range
		//1.f for absorbing 100% at each damage applies, 0.1f for absorbing 10% of damage applied and 90% moving throw armor
		void SetDamageReduction(const float newDamageReduction);

		int GetCurrentArmorPoints() const;
		//Return damage gone throw armor 
		virtual int ApplyDamage(const int damageAmount);
		//Increase armorPoints
		virtual int IncreaseArmorPoints(const int armorPointAmount);
		bool IsNotBroken() const;
	protected:
		int maxArmorPoints = 0;
		int currentArmorPoints = 0;
		float damageReduction = 1.f;
	};
}

