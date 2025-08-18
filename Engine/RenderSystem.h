#pragma once
#include <cstdint>
#include <memory>
#include <vector>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/String.hpp"
#include "SFML/Window/VideoMode.hpp"

#include "EngineAPI.h"

namespace MaxrEngine {
constexpr std::uint64_t filledMask = 0xFFFFFFFFFFFFFFFF;
class RenderSystem {
   public:
    struct LayerBitmask {
        std::uint64_t value = filledMask;
        bool GetLayerValue(const int layerNumber) const;
        void SetLayerValue(const int layerNumber, const bool value);
    };
    ENGINE_API static RenderSystem* Instance();

    ENGINE_API void SetMainWindow(sf::RenderWindow* newWindow);
    ENGINE_API sf::RenderWindow& GetMainWindow() const;
    ENGINE_API sf::RenderWindow& CrateMainWindow(const sf::VideoMode mode,
                                                 sf::String title);
    /**
     * @brief Creating layers.
     * @param layerCount - count of layers to create.
     * @return
     */
    ENGINE_API void SetUpLayers(const int layerCount);

    ENGINE_API void Render(const sf::Drawable& drawable, const int layer = 0);

    void SetView(const sf::View& view);
    void Clear(const sf::Color& clearColor = sf::Color(0, 0, 0, 0));
    void Display();

    ENGINE_API void SetActiveLayers(const LayerBitmask newActiveLayerBitmask);
    ENGINE_API LayerBitmask GetActiveLayers() const;

   private:
    sf::RenderWindow* window = nullptr;

    int layerCount = 0;
    LayerBitmask activeLayers;
    std::vector<std::unique_ptr<sf::RenderTexture>> layers;

    RenderSystem() {};
    ~RenderSystem() {};

    RenderSystem(RenderSystem const&) = delete;
    RenderSystem& operator=(RenderSystem const&) = delete;
};
}  // namespace MaxrEngine
