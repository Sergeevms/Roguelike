#pragma once
#include "BarComponent.h"
#include "IObserver.h"
#include "HealthComponent.h"

namespace Roguelike
{
	class HealthBarComponent :
		public BarComponent, public MaxrEngine::IObserver, public std::enable_shared_from_this<HealthBarComponent>
	{
	public:
		HealthBarComponent(MaxrEngine::GameObject* gameObject, MaxrEngine::Vector2Df centerOffset = { 0.f, 0.f },
			MaxrEngine::Vector2Df barSize = { 1.f, 4.f }, float borderSize = -1.f, sf::Color barColor = sf::Color::Red);

		void Update(float deltTime) override;
		void Render() override;

		void Notify(std::shared_ptr<MaxrEngine::IObservable> observable);

		void SetHealthComponent(std::shared_ptr<HealthComponent> newHealthComponent);
		std::weak_ptr<HealthComponent> GetHealthComponent() const;
	protected:
		std::weak_ptr<HealthComponent> healthComponent;
	};
}

