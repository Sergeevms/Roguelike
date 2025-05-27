#include "pch.h"
#include "ActorRegisterSystem.h"
#include "GameObject.h"
namespace MaxrEngine
{
	ActorRegisterSystem* MaxrEngine::ActorRegisterSystem::Instance()
	{
		static ActorRegisterSystem instance;
		return &instance;
	}

	const std::vector<GameObject*>& ActorRegisterSystem::GetActorsList()
	{
		return actors;
	}

	std::vector<GameObject*> ActorRegisterSystem::GetActorsInGroupList(const int groupID)
	{
		std::vector<GameObject*> actorsList;
		for (auto& actor : actors)
		{
			auto actorComponent = actor->GetComponent<ActorComponent>();
			if (actorComponent->GetGroupID() == groupID)
			{
				actorsList.push_back(actor);
			}
		}
		return actorsList;
	}

	std::vector<GameObject*> ActorRegisterSystem::GetActorsNotInGroupList(const int groupID)
	{
		std::vector<GameObject*> actorsList;
		for (auto& actor : actors)
		{
			auto actorComponent = actor->GetComponent<ActorComponent>();
			if (actorComponent->GetGroupID() != groupID)
			{
				actorsList.push_back(actor);
			}
		}
		return actorsList;
	}

	void ActorRegisterSystem::Register(ActorComponent* actor)
	{
		auto actorObject = actor->GetGameObject();
		auto it = std::find(actors.begin(), actors.end(), actorObject);
		if (it == actors.end())
		{
			actors.emplace_back(actorObject);
			std::ostringstream message;
			message << "Registered actor " << actorObject;
			LOG_INFO(message.str());
		}
		else
		{
			std::ostringstream message;
			message << actorObject << " already registered";
			LOG_WARN(message.str());
		}
	}

	void ActorRegisterSystem::UnRegister(ActorComponent* actor)
	{
		auto actorObject = actor->GetGameObject();
		actors.erase(std::remove_if(actors.begin(), actors.end(),
			[actorObject](GameObject* obj) {return actorObject == obj; }),
			actors.end());
	}
}
