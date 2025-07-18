#include "pch.h"

#include "GameObject.h"

#include <stdint.h>

#include <algorithm>
#include <iostream>

#include "TransformComponent.h"

namespace MaxrEngine {
GameObject::GameObject() {
    name = "GameObject";
    AddComponent<TransformComponent>();
}

GameObject::GameObject(const std::string& newName) {
    name = newName;
    AddComponent<TransformComponent>();
}

GameObject::~GameObject() {
    components.clear();
    children.clear();
}

std::string GameObject::GetName() const { return name; }
// NOLINTBEGIN(misc-no-recurtion) : recursive function
void GameObject::Print(int depth) {
    std::cout << std::string(static_cast<int64_t>(depth) * 2, ' ') << GetName()
              << std::endl;
    for (auto& component : components) {
        std::cout << std::string(static_cast<int64_t>(depth) * 2, ' ')
                  << "::" << component << std::endl;
    }

    for (GameObject* child : children) {
        child->Print(depth + 1);
    }
}
// NOLINTEND(misc-no-recurtion)

void GameObject::Update(float deltaTime) {
    for (auto& component : components) {
        component->Update(deltaTime);
    }
}

void GameObject::Render() {
    for (auto& component : components) {
        component->Render();
    }
}

void GameObject::AddChild(GameObject* child) { children.push_back(child); }

void GameObject::RemoveChild(GameObject* child) {
    children.erase(
        std::remove_if(children.begin(), children.end(),
                       [child](GameObject* obj) { return obj == child; }),
        children.end());
}
}  // namespace MaxrEngine