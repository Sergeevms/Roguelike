#include "pch.h"
#include "ActorComponent.h"
#include "ActorRegisterSystem.h"
#include "GameObject.h"

namespace MaxrEngine
{
	ActorComponent::ActorComponent(GameObject* gameObject)
		: Component(gameObject)
	{
		if (gameObject->GetComponent<ActorComponent>() != nullptr)
		{
			LOG_WARN("Already have ActorComponent!");
			return;
		}
		ActorRegisterSystem::Instance()->Register(this);
	}

	ActorComponent::~ActorComponent()
	{
		ActorRegisterSystem::Instance()->UnRegister(this);
	}

	void ActorComponent::Update(float deltaTime)
	{
	}

	void ActorComponent::Render()
	{
	}

	int ActorComponent::GetGroupID() const
	{
		return groupID;
	}

	void ActorComponent::SetGroupID(const int newGroupID)
	{
		groupID = newGroupID;
	}
}