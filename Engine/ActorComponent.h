#pragma once
#include "Component.h"
#include "EngineAPI.h"
namespace MaxrEngine
{
	class ENGINE_API ActorComponent :
		public Component
	{
	public:
		ActorComponent(GameObject* gameObject, int groupID = 0);
		~ActorComponent();

		virtual void Update(float deltaTime);
		virtual void Render();

		int GetGroupID() const;
		void SetGroupID(const int newGroupID);
	private:
		int groupID;
	};
}
