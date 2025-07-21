#pragma once
#include "Component.h"
#include "GameObject.h"

namespace Roguelike {
class ActorComponent : public MaxrEngine::Component {
   public:
    explicit ActorComponent(MaxrEngine::GameObject* gameObject,
                            int groupID = 0);
    ~ActorComponent();

    void Update(float deltaTime) override;
    void Render() override;

    int GetGroupID() const;
    void SetGroupID(const int newGroupID);

   private:
    int groupID;
};
}  // namespace Roguelike
