#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "GameObject.h"
#include "IFixedUpdateSystem.h"

namespace MaxrEngine {
class GameWorld {
   public:
    static GameWorld* Instance();

    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);
    void Render();
    void LateUpdate();

    GameObject* CreateGameObject();
    GameObject* CreateGameObject(std::string name);
    void DestroyGameObject(GameObject* gameObject);
    void DestroyGameObject(std::shared_ptr<GameObject> gameObject);
    void Clear();

    void RegisterFixedUpdateSytem(IFixedUpdateSystem* system);
    void UnRegisterFixedUpdateSytem(IFixedUpdateSystem* system);

    void Print() const;

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
