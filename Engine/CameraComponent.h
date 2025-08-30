#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"

#include "Component.h"
#include "TransformComponent.h"

namespace MaxrEngine {
class CameraComponent : public Component {
   public:
    explicit CameraComponent(GameObject* gameObject);
    ~CameraComponent();

    virtual void Update(float deltaTime) override;

    void SetWindow(sf::RenderWindow* newWindow);
    void ZoomBy(float newZoom);

    void SetBaseResolution(int width, int height);

   private:
    TransformComponent* transform;
    sf::RenderWindow* window = nullptr;
    sf::View* view;
};
}  // namespace MaxrEngine
