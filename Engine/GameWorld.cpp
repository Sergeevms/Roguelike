#include "pch.h"
#include "GameWorld.h"
#include "PhysicsSystem.h"

namespace MaxrEngine
{
	GameWorld* GameWorld::Instance()
	{
		static GameWorld world;
		return &world;
	}

	void GameWorld::Update(float deltaTime)
	{
		for (auto& object : gameObjects)
		{
			object->Update(deltaTime);
		}
	}

	void GameWorld::FixedUpdate(float deltaTime)
	{
		for (auto& system : fixedUpdateSystems)
		{
			system.second += deltaTime;
			if (system.second >= system.first->GetFixedUpdateTime())
			{
				system.first->Update();
				system.second -= system.first->GetFixedUpdateTime();
			}
		}		
	}

	void GameWorld::Render()
	{
		for (auto& object : gameObjects)
		{
			object->Render();
		}
	}

	void GameWorld::LateUpdate()
	{
		for (int i = static_cast<int>(markedToDestroyGameObjects.size()) - 1; i >= 0; --i)
		{
			DestroyGameObjectImmediate(markedToDestroyGameObjects[i]);
		}
	}

	GameObject* GameWorld::CreateGameObject()
	{
		GameObject* newGameObject = new GameObject();
		gameObjects.push_back(newGameObject);
		return newGameObject;
	}

	GameObject* GameWorld::CreateGameObject(std::string name)
	{
		GameObject* newGameObject = new GameObject(name);
		gameObjects.push_back(newGameObject);
		return newGameObject;
	}

	void GameWorld::DestroyGameObject(GameObject* gameObject)
	{
		markedToDestroyGameObjects.push_back(gameObject);
	}

	void GameWorld::Clear()
	{
		for (int i = static_cast<int>(gameObjects.size()) - 1; i >= 0; --i)
		{
			DestroyGameObjectImmediate(gameObjects[i]);
		}
	}

	ENGINE_API void GameWorld::RegisterFixedUpdateSytem(IFixedUpdateSytem* system)
	{
		fixedUpdateSystems[system] = 0.f;
	}

	ENGINE_API void GameWorld::UnRegisterFixedUpdateSytem(IFixedUpdateSytem* system)
	{
		auto it = fixedUpdateSystems.find(system);
		if (it != fixedUpdateSystems.end())
		{
			fixedUpdateSystems.erase(it);
		}
	}

	void GameWorld::Print() const
	{
		for (auto& obj : gameObjects)
		{
			if (obj == nullptr)
			{
				continue;
			}
			if (obj->GetComponent<TransformComponent>()->GetParent() == nullptr)
			{
				obj->Print();
			}
		}
	}

	void GameWorld::DestroyGameObjectImmediate(GameObject* gameObject)
	{
		gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(), 
			[gameObject](GameObject* obj) {return obj == gameObject; }), gameObjects.end());
		markedToDestroyGameObjects.erase(std::remove_if(markedToDestroyGameObjects.begin(), markedToDestroyGameObjects.end(), 
			[gameObject](GameObject* obj) {return obj == gameObject; }), markedToDestroyGameObjects.end());
		std::ostringstream message;
		message << gameObject << " deleted";
		LOG_INFO(message.str());
		delete gameObject;
	}
}
