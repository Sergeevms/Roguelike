#include "DevelopLevel.h"

#include "GameWorld.h"
#include "NavigationSystem.h"
#include "PlayerActor.h"
#include "Settings.h"

namespace Roguelike {
void DevelopLevel::Start() {
    LabyrinthBuilder builder;
    builder.StartBuilding({5, 5}, LabyrinthBuilder::TileType::Wall);
    LabyrinthBuilder::RectFillingParameters rectFill = {
        .bottomLeft = {0, 0},
        .size = {5, 5},
        .borderTileType = LabyrinthBuilder::TileType::Wall,
        .fillingTileType = LabyrinthBuilder::TileType::Floor};
    builder.AddRect(rectFill);
    builder.SetWall({2, 3});
    auto labyrinth = builder.ConstructLabyrinth();
    NavigationSystem::Instance()->SetUpMap(*labyrinth);
    auto player =
        std::make_shared<PlayerActor>(Settings::Instance()->playerParameters);
}
void DevelopLevel::Restart() {
    Stop();
    Start();
}
void DevelopLevel::Stop() { MaxrEngine::GameWorld::Instance()->Clear(); }
}  // namespace Roguelike
