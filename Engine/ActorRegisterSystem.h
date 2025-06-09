#pragma once
#include "ActorComponent.h"
namespace MaxrEngine
{
	class ActorRegisterSystem
	{
	public:
		ENGINE_API static ActorRegisterSystem* Instance();
		ENGINE_API const std::vector<GameObject*>& GetActorsList();
		ENGINE_API std::vector<GameObject*> GetActorsInGroupList(const int groupID);
		ENGINE_API std::vector<GameObject*> GetActorsNotInGroupList(const int groupID);
		ENGINE_API void Register(ActorComponent* actor);
		ENGINE_API void UnRegister(ActorComponent* actor);
	private:
		std::vector<GameObject*> actors;
		ActorRegisterSystem() = default;
		~ActorRegisterSystem() = default;
		ActorRegisterSystem(const ActorRegisterSystem&) = delete;
		ActorRegisterSystem& operator=(const ActorRegisterSystem&) = delete;
	};
}

