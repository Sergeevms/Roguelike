#pragma once
#include "GameObject.h"
#include "EngineAPI.h"

namespace MaxrEngine
{
	class GameWorld
	{
	public:
		ENGINE_API static GameWorld* Instance();

		void Update(float deltaTime);
		void Render();
		void LateUpdate();

		ENGINE_API GameObject* CreateGameObject();
		ENGINE_API void DestroyGameObject(GameObject* gameObject);
		ENGINE_API void Clear();
	private:
		GameWorld() {};
		~GameWorld() {};

		GameWorld(GameWorld const&) = delete;
		GameWorld& operator= (GameWorld const&) = delete;

		std::vector<GameObject*> gameObjects = {};
		std::vector<GameObject*> markedToDestroyGameObjects = {};

		void DestroyGameObjectImmediate(GameObject* gameObject);
	};
}
