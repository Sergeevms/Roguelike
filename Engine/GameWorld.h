#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "EngineAPI.h"
#include "GameObject.h"
#include "IFixedUpdateSystem.h"

namespace MaxrEngine {
class GameWorld {
   public:
    ENGINE_API static GameWorld* Instance();

    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);
    void Render();
    void LateUpdate();

    ENGINE_API GameObject* CreateGameObject();
    ENGINE_API GameObject* CreateGameObject(std::string name);
    ENGINE_API void DestroyGameObject(GameObject* gameObject);
    ENGINE_API void DestroyGameObject(std::shared_ptr<GameObject> gameObject);
    ENGINE_API void Clear();
    ENGINE_API void ClearImmediate();

    ENGINE_API void RegisterFixedUpdateSytem(IFixedUpdateSystem* system);
    ENGINE_API void UnRegisterFixedUpdateSytem(IFixedUpdateSystem* system);

    ENGINE_API void Print() const;

   private:
    GameWorld() {};
    ~GameWorld() {};

    GameWorld(GameWorld const&) = delete;
    GameWorld& operator=(GameWorld const&) = delete;

    std::unordered_map<IFixedUpdateSystem*, float> fixedUpdateSystems;

    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::vector<std::shared_ptr<GameObject>> markedToDestroyGameObjects;

    void DestroyGameObjectImmediate(std::shared_ptr<GameObject> gameObject);
};
}  // namespace MaxrEngine
