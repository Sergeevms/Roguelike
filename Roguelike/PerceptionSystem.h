#pragma once
#include <vector>

#include "GameObject.h"
#include "IFixedUpdateSytem.h"
#include "Vector.h"

namespace Roguelike

{
class OpaqueComponent;
class PerceptionComponent;

class PerceptionSystem : public MaxrEngine::IFixedUpdateSytem {
   public:
    static PerceptionSystem* Instance();

    void Update() override;
    bool CanDetect(PerceptionComponent* perceptionComponent,
                   MaxrEngine::GameObject* target) const;
    bool LineClear(const MaxrEngine::Vector2Df& startPoint,
                   const MaxrEngine::Vector2Df& endPoint) const;

    void RegisterOpaqueComponent(OpaqueComponent* component);
    void UnregisterOpaqueComponent(OpaqueComponent* component);

    void RegisterPerceptionComponent(PerceptionComponent* component);
    void UnregisterPerceptionComponent(PerceptionComponent* component);

    void ClearOpaqueObjects();
    void ClearPerceptionComponents();
    void Clear();

   private:
    std::vector<OpaqueComponent*> opaqueComponents;
    std::vector<PerceptionComponent*> perceptionComponents;
    PerceptionSystem() = default;
    ~PerceptionSystem() = default;
    PerceptionSystem(const PerceptionSystem&) = delete;
    PerceptionSystem& operator=(const PerceptionSystem&) = delete;
};
}  // namespace Roguelike
