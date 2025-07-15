#include "OpaqueComponent.h"

#include "PerceptionSystem.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"

namespace Roguelike {
OpaqueComponent::OpaqueComponent(MaxrEngine::GameObject* gameObject)
    : Component(gameObject) {
    PerceptionSystem::Instance()->RegisterOpaqueComponent(this);
}

OpaqueComponent::~OpaqueComponent() {
    PerceptionSystem::Instance()->UnregisterOpaqueComponent(this);
}

void OpaqueComponent::Update(float deltaTime) {}

void OpaqueComponent::Render() {}
}  // namespace Roguelike
