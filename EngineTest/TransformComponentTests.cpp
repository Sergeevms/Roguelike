#include "pch.h"
#include "TransformComponent.h"
#include "GameWorld.h"

constexpr float EPS = 5e-6;
TEST(TransformComponent, Constructor)
{
	MaxrEngine::TransformComponent* component = new MaxrEngine::TransformComponent(nullptr);
	MaxrEngine::Vector2Df zeroVector;
	MaxrEngine::Vector2Df oneVector (1.f, 1.f);
	EXPECT_EQ(component->GetLocalPosition(), zeroVector);
	EXPECT_EQ(component->GetLocalScale(), oneVector);
	EXPECT_EQ(component->GetWorldPosition(), zeroVector);
	EXPECT_EQ(component->GetWorldScale(), oneVector);
	EXPECT_EQ(component->GetLocalRotation(), 0.f);
	EXPECT_EQ(component->GetWorldRotation(), 0.f);
	delete component;
}

TEST(TransformComponent, MoveBy)
{
	MaxrEngine::TransformComponent* transform = new MaxrEngine::TransformComponent(nullptr);
	MaxrEngine::Vector2Df zeroVector;
	MaxrEngine::Vector2Df oneVector(1.f, 1.f);
	MaxrEngine::Vector2Df vector(3.f, 10.f);
	transform->MoveBy(vector);
	EXPECT_EQ(transform->GetLocalPosition(), vector);
	EXPECT_EQ(transform->GetLocalScale(), oneVector);
	EXPECT_EQ(transform->GetWorldPosition(), vector);
	EXPECT_EQ(transform->GetWorldScale(), oneVector);
	EXPECT_EQ(transform->GetLocalRotation(), 0.f);
	EXPECT_EQ(transform->GetWorldRotation(), 0.f);
	delete transform;
}

TEST(TransformComponent, ScaleBy)
{
	MaxrEngine::TransformComponent* transform = new MaxrEngine::TransformComponent(nullptr);
	MaxrEngine::Vector2Df zeroVector;
	MaxrEngine::Vector2Df vector(3.f, 10.f);
	transform->ScaleBy(vector);
	EXPECT_EQ(transform->GetLocalPosition(), zeroVector);
	EXPECT_EQ(transform->GetLocalScale(), vector);
	EXPECT_EQ(transform->GetWorldPosition(), zeroVector);
	EXPECT_EQ(transform->GetWorldScale(), vector);
	EXPECT_EQ(transform->GetLocalRotation(), 0.f);
	EXPECT_EQ(transform->GetWorldRotation(), 0.f);
	delete transform;
}

TEST(TransformComponent, RotateBy)
{
	MaxrEngine::TransformComponent* transform = new MaxrEngine::TransformComponent(nullptr);
	MaxrEngine::Vector2Df zeroVector;
	MaxrEngine::Vector2Df oneVector(1.f, 1.f);
	float angle = 75.f;
	transform->RotateBy(angle);
	EXPECT_EQ(transform->GetLocalPosition(), zeroVector);
	EXPECT_EQ(transform->GetLocalScale(), oneVector);
	EXPECT_EQ(transform->GetWorldPosition(), zeroVector);
	EXPECT_EQ(transform->GetWorldScale(), oneVector);
	EXPECT_EQ(transform->GetLocalRotation(), angle);
	EXPECT_EQ(transform->GetWorldRotation(), angle);
	delete transform;
}

TEST(TransformComponent, RotationMovingScaling)
{
	MaxrEngine::TransformComponent* transform = new MaxrEngine::TransformComponent(nullptr);
	MaxrEngine::Vector2Df zeroVector;
	MaxrEngine::Vector2Df oneVector(1.f, 1.f);
	MaxrEngine::Vector2Df moveVector(10.f, 0.f);
	MaxrEngine::Vector2Df scaleVector(0.5f, 1.f);
	float angle = 90.f;
	transform->RotateBy(angle);
	transform->MoveBy(moveVector);
	transform->ScaleBy(scaleVector);
	EXPECT_EQ(transform->GetLocalPosition(), moveVector);
	EXPECT_EQ(transform->GetLocalScale(), scaleVector);
	EXPECT_EQ(transform->GetWorldPosition(), moveVector);
	EXPECT_EQ(transform->GetWorldScale(), scaleVector);
	EXPECT_EQ(transform->GetLocalRotation(), angle);
	EXPECT_EQ(transform->GetWorldRotation(), angle);
	delete transform;
}

TEST(TransformComponent, ParentRotation)
{
	MaxrEngine::GameObject* parentObject = MaxrEngine::GameWorld::Instance()->CreateGameObject();
	MaxrEngine::TransformComponent* transform = parentObject->GetComponent<MaxrEngine::TransformComponent>();
	MaxrEngine::Vector2Df zeroVector;
	MaxrEngine::Vector2Df oneVector(1.f, 1.f);
	MaxrEngine::GameObject* childObject = MaxrEngine::GameWorld::Instance()->CreateGameObject();
	MaxrEngine::TransformComponent* connectedTransform = childObject->GetComponent<MaxrEngine::TransformComponent>();
	connectedTransform->SetParent(transform);
	transform->Print();
	connectedTransform->Print();
	float zeroAngle = 0.f;
	float angle = 45.f;
	transform->RotateBy(angle);
	transform->Print();
	connectedTransform->Print();
	EXPECT_NEAR(connectedTransform->GetLocalPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalRotation(), zeroAngle, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldRotation(), angle, EPS);
	transform->RotateBy(-angle);
	transform->Print();
	connectedTransform->Print();
	EXPECT_NEAR(connectedTransform->GetLocalPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalRotation(), zeroAngle, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldRotation(), zeroAngle, EPS);
}

TEST(TransformComponent, ParentMoving)
{
	MaxrEngine::GameObject* parentObject = MaxrEngine::GameWorld::Instance()->CreateGameObject();
	MaxrEngine::TransformComponent* transform = parentObject->GetComponent<MaxrEngine::TransformComponent>();
	MaxrEngine::Vector2Df zeroVector;
	MaxrEngine::Vector2Df oneVector(1.f, 1.f);
	float zeroAngle = 0.f;
	MaxrEngine::GameObject* childObject = MaxrEngine::GameWorld::Instance()->CreateGameObject();
	MaxrEngine::TransformComponent* connectedTransform = childObject->GetComponent<MaxrEngine::TransformComponent>();
	connectedTransform->SetParent(transform);
	transform->Print();
	connectedTransform->Print();
	MaxrEngine::Vector2Df moveVector(10.f, 5.f);
	transform->MoveBy(moveVector);
	transform->Print();
	connectedTransform->Print();
	EXPECT_NEAR(connectedTransform->GetLocalPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().x, moveVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().y, moveVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalRotation(), zeroAngle, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldRotation(), zeroAngle, EPS);
	transform->MoveBy(-moveVector);
	transform->Print();
	connectedTransform->Print();
	EXPECT_NEAR(connectedTransform->GetLocalPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalRotation(), zeroAngle, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldRotation(), zeroAngle, EPS);
}

TEST(TransformComponent, ParentScaling)
{
	MaxrEngine::GameObject* parentObject = MaxrEngine::GameWorld::Instance()->CreateGameObject();
	MaxrEngine::TransformComponent* transform = parentObject->GetComponent<MaxrEngine::TransformComponent>();
	MaxrEngine::Vector2Df zeroVector;
	MaxrEngine::Vector2Df oneVector(1.f, 1.f);
	float zeroAngle = 0.f;
	MaxrEngine::GameObject* childObject = MaxrEngine::GameWorld::Instance()->CreateGameObject();
	MaxrEngine::TransformComponent* connectedTransform = childObject->GetComponent<MaxrEngine::TransformComponent>();
	connectedTransform->SetParent(transform);
	transform->Print();
	connectedTransform->Print();
	MaxrEngine::Vector2Df scaleVector(10.f, 5.f);
	transform->ScaleBy(scaleVector);
	transform->Print();
	connectedTransform->Print();
	EXPECT_NEAR(connectedTransform->GetLocalPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().x, scaleVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().y, scaleVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalRotation(), zeroAngle, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldRotation(), zeroAngle, EPS);
	MaxrEngine::Vector2Df reverseScaleVector(1 / 10.f, 1 / 5.f);
	transform->ScaleBy(reverseScaleVector);
	transform->Print();
	connectedTransform->Print();
	EXPECT_NEAR(connectedTransform->GetLocalPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalRotation(), zeroAngle, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldRotation(), zeroAngle, EPS);
}

TEST(TransformComponent, ParentRotationMovingScaling)
{
	MaxrEngine::GameObject * parentObject = MaxrEngine::GameWorld::Instance()->CreateGameObject();
	MaxrEngine::TransformComponent* transform = parentObject->GetComponent<MaxrEngine::TransformComponent>();
	MaxrEngine::Vector2Df zeroVector;
	MaxrEngine::Vector2Df oneVector(1.f, 1.f);
	MaxrEngine::Vector2Df moveVector(10.f, 4.f);
	MaxrEngine::Vector2Df scaleVector(0.5f, 4.f);
	MaxrEngine::Vector2Df reverseScaleVector(2.f, 0.25f);
	float zeroAngle = 0.f;
	float angle = 90.f;
	MaxrEngine::GameObject* childObject = MaxrEngine::GameWorld::Instance()->CreateGameObject();
	MaxrEngine::TransformComponent* connectedTransform = childObject->GetComponent<MaxrEngine::TransformComponent>();
	connectedTransform->SetParent(transform);
	transform->Print();
	connectedTransform->Print();
	transform->RotateBy(angle);
	transform->MoveBy(moveVector);
	transform->ScaleBy(scaleVector);
	transform->Print();
	connectedTransform->Print();
	EXPECT_NEAR(connectedTransform->GetLocalPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().x, moveVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().y, moveVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().x, scaleVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().y, scaleVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalRotation(), zeroAngle, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldRotation(), angle, EPS);
	MaxrEngine::Vector2Df reverseMove = -moveVector;
	transform->ScaleBy(reverseScaleVector);
	transform->RotateBy(-angle);
	transform->MoveBy(reverseMove);
	transform->Print();
	connectedTransform->Print();
	EXPECT_NEAR(connectedTransform->GetLocalPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().x, zeroVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldPosition().y, zeroVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().x, oneVector.x, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldScale().y, oneVector.y, EPS);
	EXPECT_NEAR(connectedTransform->GetLocalRotation(), zeroAngle, EPS);
	EXPECT_NEAR(connectedTransform->GetWorldRotation(), zeroAngle, EPS);
}