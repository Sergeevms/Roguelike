#include "pch.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "MovementComponent.h"
#include "RigidBodyComponent.h"
#include "SpriteAnimationComponent.h"

constexpr float EPS = 5e-6F;
TEST(GameObject, Constructor) {
    MaxrEngine::GameObject* gameObject =
        MaxrEngine::GameWorld::Instance()->CreateGameObject();
    MaxrEngine::TransformComponent* component =
        gameObject->GetComponent<MaxrEngine::TransformComponent>();
    EXPECT_FALSE(component == nullptr);
}

TEST(GameObject, AddComponent) {
    MaxrEngine::GameObject* gameObject =
        MaxrEngine::GameWorld::Instance()->CreateGameObject();
    auto component = gameObject->AddComponent<MaxrEngine::MovementComponent>();
    EXPECT_FALSE(component == nullptr);
}

TEST(GameObject, RemoveComponent) {
    MaxrEngine::GameObject* gameObject =
        MaxrEngine::GameWorld::Instance()->CreateGameObject();
    auto component =
        gameObject->AddComponent<MaxrEngine::SpriteAnimationComponent>();
    EXPECT_FALSE(component == nullptr);
    gameObject->RemoveComponent(component);
    auto removed =
        gameObject->GetComponent<MaxrEngine::SpriteAnimationComponent>();
    EXPECT_TRUE(removed == nullptr);
}

TEST(GameObject, GetChildComponent) {
    MaxrEngine::GameObject* gameObject =
        MaxrEngine::GameWorld::Instance()->CreateGameObject();
    auto child = MaxrEngine::GameWorld::Instance()->CreateGameObject();
    gameObject->AddChild(child);
    child->AddComponent<MaxrEngine::SpriteAnimationComponent>();
    auto component =
        gameObject
            ->GetComponentInChildren<MaxrEngine::SpriteAnimationComponent>();
    EXPECT_TRUE(component != nullptr);
    auto anotherComponent =
        gameObject->GetComponentInChildren<MaxrEngine::RigidBodyComponent>();
    EXPECT_TRUE(anotherComponent == nullptr);
}