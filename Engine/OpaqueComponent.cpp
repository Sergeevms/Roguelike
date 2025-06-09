#include "pch.h"
#include "OpaqueComponent.h"
#include "PerceptionSystem.h"
#include "ResourceSystem.h"
#include "RenderSystem.h"

namespace MaxrEngine
{
	OpaqueComponent::OpaqueComponent(GameObject* gameObject)
		: Component(gameObject)
	{
		PerceptionSystem::Instance()->RegisterOpaqueComponent(this);
	}

	OpaqueComponent::~OpaqueComponent()
	{
		PerceptionSystem::Instance()->UnregisterOpaqueComponent(this);
	}

	void OpaqueComponent::Update(float deltaTime)
	{
	}

	void OpaqueComponent::Render()
	{
	}
}
