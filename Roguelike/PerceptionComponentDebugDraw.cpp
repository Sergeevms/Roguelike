#include "pch.h"
#include "PerceptionComponentDebugDraw.h"
#include "RenderSystem.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>

namespace Roguelike
{
	PerceptionComponentDebugDraw::PerceptionComponentDebugDraw(MaxrEngine::GameObject* gameObject)
		: Component(gameObject)
	{
		perceptionComponent = gameObject->GetComponentSharedPtr<PerceptionComponent>();
		if (perceptionComponent.expired())
		{
			LOG_WARN("PerceptionComponentDebugDraw needs PerceptionComponent");
			gameObject->RemoveComponent(this);
			return;
		}	
	}

	void PerceptionComponentDebugDraw::Update(float deltaTime)
	{

	}

	void PerceptionComponentDebugDraw::Render()
	{
		if (auto perception = perceptionComponent.lock())
		{
			auto& position = gameObject->GetComponent<MaxrEngine::TransformComponent>()->GetWorldPosition();
			sf::CircleShape senseZone(perception->GetSenseRadius());			
			senseZone.setFillColor(sf::Color::Transparent);
			senseZone.setOutlineColor(sf::Color::Red);
			senseZone.setOutlineThickness(-2.f);
			senseZone.setPosition(Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position));
			auto rect = senseZone.getLocalBounds();
			senseZone.setOrigin(rect.width / 2.f, rect.height / 2.f);
			MaxrEngine::RenderSystem::Instance()->Render(senseZone);
			sf::VertexArray visionDirection(sf::PrimitiveType::LineStrip, 2);			
			auto direction = Normalized(perception->GetVisionDirection()) * perception->GetVisionRadius();
			visionDirection[0] = sf::Vertex(Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position), sf::Color::Green);
			visionDirection[1] = sf::Vertex(Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position + direction), sf::Color::Green);
			MaxrEngine::RenderSystem::Instance()->Render(visionDirection);
			auto perceptionAngle = perception->GetVisionAngle();
			if (perceptionAngle < 360.f)
			{
				//Additional 3 vertexex for cone center (as start and end) and arc start
				sf::VertexArray visionCone(sf::PrimitiveType::LineStrip);
				visionCone.append(sf::Vertex(Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position), sf::Color::Yellow));
				Rotate(direction, -perceptionAngle / 2.f);
				visionCone.append(sf::Vertex(Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position + direction), sf::Color::Yellow));
				auto angleStep = perceptionAngle / arcLinesCount;
				for (unsigned i = 0; i < arcLinesCount; ++i)
				{
					Rotate(direction, perceptionAngle / arcLinesCount);
					visionCone.append(sf::Vertex(Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position + direction), sf::Color::Yellow));
				}
				visionCone.append(sf::Vertex(Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position), sf::Color::Yellow));
				MaxrEngine::RenderSystem::Instance()->Render(visionCone);
			}
			else
			{
				sf::CircleShape visionZone(perception->GetVisionRadius());
				visionZone.setFillColor(sf::Color::Transparent);
				visionZone.setOutlineColor(sf::Color::Yellow);
				visionZone.setOutlineThickness(-2.f);
				visionZone.setPosition(Convert<sf::Vector2f, MaxrEngine::Vector2Df>(position));
				MaxrEngine::RenderSystem::Instance()->Render(visionZone);
			}
		}
		else
		{
			LOG_WARN("PerceptionComponentDebugDraw needs PerceptionComponent");
		}
	}

	void PerceptionComponentDebugDraw::setArcPointCount(unsigned newArcPointsCount)
	{
		arcLinesCount = newArcPointsCount;
	}
}