#include "pch.h"

#include "TransformComponent.h"

TEST(TransformComponent, Constuctor) {
    Engine::TransformComponent component(nullptr);
    EXPECT_EQ(1, 1);
}