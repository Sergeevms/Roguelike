#include "DeveloperLevel.h"
#include "GameWorld.h"
#include "Settings.h"

namespace Roguelike
{
    void DeveloperLevel::Start() 
    {
        auto settings = Settings::Instance();
        MaxrEngine::Vector2Df testWallPosition = { 0.f, 0.f };
        MaxrEngine::Vector2Di testWallSize = { settings->mapTileSize, settings->mapTileSize };
        testWall = std::make_shared<Wall>(testWallPosition, 0, testWallSize);
        player = std::make_shared<Player>();
    }

    void DeveloperLevel::Restart()
    {
        Stop();
        Start();
    }

    void DeveloperLevel::Stop()
    {
        MaxrEngine::GameWorld::Instance()->Clear();
    }
}