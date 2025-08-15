#include "pch.h"

#include "RenderSystem.h"

#include <algorithm>
#include <cassert>
#include <memory>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/String.hpp"
#include "SFML/Window/VideoMode.hpp"

#include "Logger.h"

namespace MaxrEngine {
RenderSystem* RenderSystem::Instance() {
    static RenderSystem render;
    return &render;
}

void RenderSystem::SetMainWindow(sf::RenderWindow* newWindow) {
    window = newWindow;
}

sf::RenderWindow& RenderSystem::GetMainWindow() const { return *window; }

sf::RenderWindow& RenderSystem::CrateMainWindow(const sf::VideoMode mode,
                                                sf::String title) {
    window = new sf::RenderWindow(mode, title);
    return *window;
}

void RenderSystem::SetUpLayers(const int layerCount) {
    assert(layerCount >= 1 && "Layer count should be positive!");
    if (layerCount < 1) {
        LOG_ERROR("Layer count should be positive!");
        return;
    }
    layers.clear();
    layers.resize(layerCount);
    auto size = window->getSize();
    for (auto& layer : layers) {
        layer = std::make_unique<sf::RenderTexture>();
        layer->create(size.x, size.y);
    }
    RenderSystem::layerCount = layerCount;
}
void RenderSystem::SetView(const sf::View& view) {
    for (auto& layer : layers) {
        layer->setView(view);
    }
}
void RenderSystem::Clear(const sf::Color& clearColor) {
    window->clear(clearColor);
    for (auto& layer : layers) {
        layer->clear(clearColor);
    }
}
void RenderSystem::Render(const sf::Drawable& drawable, const int layer) {
    const int clampedLayer = std::clamp(layer, 0, layerCount - 1);
    layers[clampedLayer]->draw(drawable);
}
void RenderSystem::Display() {
    for (auto& layer : layers) {
        layer->display();
        const sf::Sprite sprite(layer->getTexture());
        window->draw(sprite);
    }
    window->display();
}
}  // namespace MaxrEngine