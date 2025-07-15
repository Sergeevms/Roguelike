#include "pch.h"
#include "Component.h"
#include <iostream>
#include <cassert>

namespace MaxrEngine
{
	Component::Component(GameObject* gameObject) : gameObject(gameObject) 
	{
		assert(gameObject != nullptr && "GameObject pointer must not be null");
		if (gameObject == nullptr)
		{
			LOG_WARN("Component with nullptr GameOnject constructed");
		}
	}

	Component::~Component()
	{	
		std::ostringstream message;
		message << "Deleted component: " << typeid(this).name() << " " <<  this << std::endl;
		LOG_INFO(message.str());
	}

	GameObject* Component::GetGameObject()
	{
		return gameObject;
	}
	
}