#include "pch.h"
#include "MovementComponent.h"

namespace MaxrEngine
{
	MovementComponent::MovementComponent(GameObject* gameObject) :
		Component(gameObject)
	{
		input = gameObject->GetComponent<InputComponent>();
		transform = gameObject->GetComponent<TransformComponent>();

		if (input == nullptr)
		{
			std::cout << "Need InputComponent for movement." << std::endl;
		}
	}

	void MovementComponent::Update(float deltaTime)
	{
		Vector2Df direction = Vector2Df{ input->GetHorizontalAxis(), input->GetVerticalAxis() };

		transform->MoveBy(speed * deltaTime * direction);

		acceleration = transform->GetWorldPosition() - previosPosition;
		previosPosition = transform->GetWorldPosition();
	}

	void MovementComponent::Render()
	{
	}

	void MovementComponent::SetSpeed(float newSpeed)
	{
		speed = newSpeed;
	}

	float MovementComponent::GetSpeed() const
	{
		return speed;
	}

	float MovementComponent::GetAccelerationSquared() const
	{
		Vector2Df squaredAcceleration = acceleration * acceleration;
		return squaredAcceleration.x + squaredAcceleration.y;
	}
}