#pragma once
#include "Component.h"
#include "EngineAPI.h"
namespace Roguelike
{
	class ActorComponent :
		public MaxrEngine::Component
	{
	public:
		ActorComponent(MaxrEngine::GameObject* gameObject, int groupID = 0);
		~ActorComponent();

		virtual void Update(float deltaTime);
		virtual void Render();

		int GetGroupID() const;
		void SetGroupID(const int newGroupID);
	private:
		int groupID;
	};
}
