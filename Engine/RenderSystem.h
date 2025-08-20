#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

#include "EngineAPI.h"

namespace MaxrEngine {
class ENGINE_API RenderSystem {
   public:
    static RenderSystem* Instance();

    void SetMainWindow(sf::RenderWindow* newWindow);
    sf::RenderWindow& GetMainWindow() const;
    sf::RenderWindow& CrateMainWindow(const sf::VideoMode mode,
                                      sf::String title);

    void Render(const sf::Drawable& drawable);

   private:
    sf::RenderWindow* window = nullptr;

    RenderSystem() {};
    ~RenderSystem() {};

    RenderSystem(RenderSystem const&) = delete;
    RenderSystem& operator=(RenderSystem const&) = delete;
};
}  // namespace MaxrEngine
