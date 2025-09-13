#ifdef ROGUELIKE_DEVELOPER_LEVEL
#include "DevelopLevel.h"

#include <memory>

#include "GameWorld.h"
#include "LabyrinthBuilder.h"
#include "NavigationSystem.h"
#include "NavigationSystemDebugRendererComponent.h"
#include "PlayerActor.h"
#include "Settings.h"

namespace Roguelike {
void DevelopLevel::Start() {
    LabyrinthBuilder builder;
    builder.StartBuilding({5, 5}, LabyrinthBuilder::TileType::Wall);
    const LabyrinthBuilder::RectFillingParameters rectFill = {
        .bottomLeft = {0, 0},
        .size = {5, 5},
        .borderTileType = LabyrinthBuilder::TileType::Wall,
        .fillingTileType = LabyrinthBuilder::TileType::Floor};
    builder.AddRect(rectFill);
    builder.SetWall({2, 3});
    builder.SetWall({2, 2});
    auto labyrinth = builder.ConstructLabyrinth();
    auto* debugNavSystem = MaxrEngine::GameWorld::Instance()->CreateGameObject(
        "Nav system debug render");
    auto debugRender =
        debugNavSystem->AddComponent<NavigationSystemDebugRendererComponent>(
            static_cast<int>(Settings::RenderLayers::Debug));
    NavigationSystem::Instance()->AddObserver(debugRender);
    NavigationSystem::Instance()->SetUpMap(labyrinth);
    auto player =
        std::make_shared<PlayerActor>(Settings::Instance()->playerParameters);
}
void DevelopLevel::Restart() {
    Stop();
    Start();
}
void DevelopLevel::Stop() { MaxrEngine::GameWorld::Instance()->Clear(); }
}  // namespace Roguelike
#endif  // ROGUELIKE_DEVELOPER_LEVEL