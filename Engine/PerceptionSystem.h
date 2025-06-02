#pragma once
#include "IFixedUpdateSytem.h"
#include "Vector.h"
#include "GameObject.h"

namespace MaxrEngine
{
	class OpaqueComponent;
	class PerceptionComponent;

	class PerceptionSystem
		: public IFixedUpdateSytem
	{
	public:
		static PerceptionSystem* Instance();

		void Update() override;
		bool CanDetect(PerceptionComponent* perception, GameObject* target) const;
		bool LineClear(const Vector2Df& startPoint, const Vector2Df& endPoint) const;

		void RegisterOpaqueComponent(OpaqueComponent* component);
		void UnregisterOpaqueComponent(OpaqueComponent* component);

		void RegisterPerceptionComponent(PerceptionComponent* component);
		void UnregisterPerceptionComponent(PerceptionComponent* component);

		void ClearOpaqueObjects();
		void ClearPerceptionComponents();
		void Clear();
	private:
		std::vector<OpaqueComponent*> opaqueComponents;
		std::vector<PerceptionComponent*> perceptionComponents;
		PerceptionSystem() = default;
		~PerceptionSystem() = default;
		PerceptionSystem(const PerceptionSystem&) = delete;
		PerceptionSystem& operator=(const PerceptionSystem&) = delete;
	};
}

