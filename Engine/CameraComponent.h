#pragma once
#include "Component.h"
#include "EngineAPI.h"
#include "TransformComponent.h"

namespace MaxrEngine {
class ENGINE_API CameraComponent : public Component {
   public:
    CameraComponent(GameObject* gameObject);
    ~CameraComponent();

    virtual void Update(float deltaTime) override;
    virtual void Render() override;

    void SetWindow(sf::RenderWindow* newWindow);
    void ZoomBy(float newZoom);

    void SetBaseResolution(int width, int height);

   private:
    TransformComponent* transform;
    sf::RenderWindow* window = nullptr;
    sf::View* view;
};
}  // namespace MaxrEngine
