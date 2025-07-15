#ifndef ROGUELIKE_ACTORREGISTERSISTEM_H
#define ROGUELIKE_ACTORREGISTERSISTEM_H
#include <vector>

#include "ActorComponent.h"
#include "Gameobject.h"
namespace Roguelike {
class ActorRegisterSystem {
   public:
    static ActorRegisterSystem* Instance();
    const std::vector<MaxrEngine::GameObject*>& GetActorsList();
    std::vector<MaxrEngine::GameObject*> GetActorsInGroupList(
        const int groupID);
    std::vector<MaxrEngine::GameObject*> GetActorsNotInGroupList(
        const int groupID);
    void Register(ActorComponent* actor);
    void UnRegister(ActorComponent* actor);

   private:
    std::vector<MaxrEngine::GameObject*> actors;
    ActorRegisterSystem() = default;
    ~ActorRegisterSystem() = default;
    ActorRegisterSystem(const ActorRegisterSystem&) = delete;
    ActorRegisterSystem& operator=(const ActorRegisterSystem&) = delete;
};
}  // namespace Roguelike
#endif  // ROGUELIKE_ACTORREGISTERSISTEM_H
