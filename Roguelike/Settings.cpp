#include "Settings.h"

#include "SFML/Graphics/Color.hpp"

#include "Utility.h"
#include "Vector.h"

namespace Roguelike {
const SettingsStruct Settings::defaultsSettings{
    .screenWidth = 1280,
    .screenHeight = 720,
    .gameName = L"Roguelike",

    .resourcesPath = "Resources\\",
    .soundPath = "Resources\\Sounds\\",
    .fontPath = "Resources\\Fonts\\",
    .texturePath = "Resources\\Textures\\",
    .textureMapsPath = "Resources\\TextureMaps\\",

    .playerSize = 70,
    .playerSpeed = 400.0F,

    .enemySpeed = 200.0F,

    .enemyPerceptionParameters = {.visionAngle = 145.0F,
                                  .visionRadius = 300.0F,
                                  .visionDirectionX = -1.0F,
                                  .visionDirectionY = 0.0F,
                                  .senseRadius = 150.0F},
    .enemyChaseMaxRadius = 300.0F,
    .enemyChaseMinRadius = 40.0F,

    .mapTileSize = 90,

    .playerHealth = 200.0F,
    .enemyHealth = 100.0F,
    .armorDamageReduction = 0.75F,
    .attackRange = 100.0F,
    .attackCooldown = 2.0F,
    .attackDamage = 30.0F,

    .healthBarParameters = {.centerOffset = {0.0F, 35.0F},
                            .barSize = {32.0F, 5.0F},
                            .barColor = sf::Color(255, 0, 0),
                            .borderSize = -1.0F},

    .armorBarParameters = {.centerOffset = {0.0F, 41.0F},
                           .barSize = {32.0F, 5.0F},
                           .barColor = sf::Color(255, 255, 0),
                           .borderSize = -1.0F},

    .labyrinthParameters = {.width = 11,
                            .heigth = 11,
                            .isAdjustingSizeAndStart = true,
                            .randSeed = -1}};

MaxrEngine::Vector2Df Settings::ScreenCenter() const {
    return Half(ScreenSize());
}

MaxrEngine::Vector2Df Settings::ScreenSize() const {
    return MaxrEngine::Vector2Df(
        {static_cast<float>(screenWidth), static_cast<float>(screenHeight)});
}
float Settings::PlayerSizeF() const { return static_cast<float>(playerSize); }
}  // namespace Roguelike
