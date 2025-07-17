#include "Settings.h"

#include "Utility.h"
#include "Vector.h"

namespace Roguelike {
// NOLINTBEGIN(readability-magic-numbers)
Settings::Settings() {
    resourcesPath = "Resources\\";
    soundPath = resourcesPath + "Sounds\\";
    fontPath = resourcesPath + "Fonts\\";
    texturePath = resourcesPath + "Textures\\";
    textureMapsPath = resourcesPath + "TextureMaps\\";

    screenWidth = 1280;
    screenHeight = 720;
    gameName = L"Roguelike";
    playerSize = 32;
    playerSpeed = 400.0F;
    mapTileSize = 36;

    enemySpeed = Half(playerSpeed);
    enemyVisionRadius = 300.0F;
    enemyVisionAngle = 145.0F;
    enemySenseRadius = 150.0F;
    enemyChaseMaxRadius = enemyVisionRadius;
    enemyChaseMinRadius = 40.0F;

    playerHealth = 200.0F;
    enemyHealth = 100.0F;
    armorDamageReduction = 0.75F;
    attackRange = 100.0F;
    attackCooldown = 2.0F;
    attackDamage = 30.0F;

    healthBarDistance = 4.0F;
    barHeight = 5.F;
    barBorder = 1.F;
    armorBarDistance = 2.0F * healthBarDistance + barHeight;
}
// NOLINTEND(readability-magic-numbers)

MaxrEngine::Vector2Df Settings::ScreenCenter() const {
    return Half(ScreenSize());
}

MaxrEngine::Vector2Df Settings::ScreenSize() const {
    return MaxrEngine::Vector2Df(
        {static_cast<float>(screenWidth), static_cast<float>(screenHeight)});
}
float Settings::PlayerSizeF() const { return static_cast<float>(playerSize); }
}  // namespace Roguelike
