#include "pch.h"
#include "CameraComponent.h"
#include <iostream>
#include <cassert>

namespace MaxrEngine
{
	CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
	{
		view = new sf::View(sf::FloatRect(0, 0, 800, -600));
		transform = gameObject->GetComponent<TransformComponent>();
	}

	CameraComponent::~CameraComponent()
	{
		delete view;
	}

	void CameraComponent::Update(float deltaTime)
	{
		auto position = transform->GetWorldPosition();
		auto rotation = transform->GetWorldRotation();

		view->setCenter(Convert<sf::Vector2f, Vector2Df>(position));
		view->setRotation(rotation);

		window->setView(*view);
	}

	void CameraComponent::Render()
	{
		assert(window != nullptr && "NULL window render");
		if (!window)
		{
			LOG_ERROR("NULL window render.");
		}
	}

	void CameraComponent::SetWindow(sf::RenderWindow* newWindow)
	{
		window = newWindow;
	}

	void CameraComponent::ZoomBy(float newZoom)
	{
		assert(newZoom > 0.f && "Not allowed zoom lesser or equal than zero.");
		if (newZoom <= 0)
		{
			LOG_WARN("Not allowed zoom lesser or equal than zero.");
			return;
		}
		view->zoom(newZoom);
	}

	void CameraComponent::SetBaseResolution(int width, int height)
	{
		view->reset(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(-height)));
	}
}