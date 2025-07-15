#pragma once
#include "GameObject.h"
#include "EngineAPI.h"
#include "IFixedUpdateSytem.h"
#include <unordered_map>

namespace MaxrEngine
{
	class GameWorld
	{
	public:
		ENGINE_API static GameWorld* Instance();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();
		void LateUpdate();

		ENGINE_API GameObject* CreateGameObject();
		ENGINE_API GameObject* CreateGameObject(std::string name);
		ENGINE_API void DestroyGameObject(GameObject* gameObject);
		ENGINE_API void DestroyGameObject(std::shared_ptr <GameObject> gameObject);
		ENGINE_API void Clear();

		ENGINE_API void RegisterFixedUpdateSytem(IFixedUpdateSytem* system);
		ENGINE_API void UnRegisterFixedUpdateSytem(IFixedUpdateSytem* system);

		ENGINE_API void Print() const;
	private:
		GameWorld() {};
		~GameWorld() {};

		GameWorld(GameWorld const&) = delete;
		GameWorld& operator= (GameWorld const&) = delete;

		std::unordered_map<IFixedUpdateSytem*, float> fixedUpdateSystems;

		std::vector<std::shared_ptr<GameObject>> gameObjects = {};
		std::vector<std::shared_ptr<GameObject>> markedToDestroyGameObjects = {};

		void DestroyGameObjectImmediate(std::shared_ptr<GameObject> gameObject);
	};
}
