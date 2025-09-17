#ifdef ROGUELIKE_DEVELOPER_LEVEL
#include "DevelopLevel.h"

#include <memory>
#include <utility>
#include <vector>

#include "AIActor.h"
#include "AIActorManagerSystem.h"
#include "AIBlackboard.h"
#include "AIControlComponent.h"
#include "BTIdle.h"
#include "BTMoveAlongPath.h"
#include "BTMoveToPoint.h"
#include "BTNode.h"
#include "GameWorld.h"
#include "LabyrinthBuilder.h"
#include "NavigationSystem.h"
#include "NavigationSystemDebugRendererComponent.h"
#include "PlayerActor.h"
#include "Settings.h"
#include "Vector.h"

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
    /*builder.SetWall({2, 3});
    builder.SetWall({2, 2});*/
    auto labyrinth = builder.ConstructLabyrinth();
    AIActorManagerSystem::Instance()->Reset(
        labyrinth->GetLabyrinthCoodinatesRect());
    auto* debugNavSystem = MaxrEngine::GameWorld::Instance()->CreateGameObject(
        "Nav system debug render");
    auto debugRender =
        debugNavSystem->AddComponent<NavigationSystemDebugRendererComponent>(
            static_cast<int>(Settings::RenderLayers::Debug));
    NavigationSystem::Instance()->AddObserver(debugRender);
    NavigationSystem::Instance()->SetUpMap(labyrinth);
    auto player =
        std::make_shared<PlayerActor>(Settings::Instance()->playerParameters);
    auto ai = AIActorManagerSystem::Instance()->SpawnActorAt(
        Settings::Instance()->aiParameters,
        labyrinth->GetCellCoordinates({1, 1}));

    auto* chase = ai->GetGameObject()->GetComponent<AIChaseTargetComponent>();
    ai->GetGameObject()->RemoveComponent(chase);

    std::unique_ptr<BTNode> node = std::make_unique<BTSequence>();
    BTComposite* root = dynamic_cast<BTComposite*>(node.get());
    auto control = ai->GetGameObject()->AddComponent<AIControlComponent>();
    control->SetBTRoot(std::move(node));

    auto* blackboard = ai->GetGameObject()->GetComponent<AIBlackboard>();

    BTIdle::SetUpBlackboard(blackboard, 2.F);
    node = std::make_unique<BTIdle>();
    root->AddChild(std::move(node));

    BTLookAroundIdle::SetUpBlackboard(blackboard, 3.f);
    node = std::make_unique<BTLookAroundIdle>();
    root->AddChild(std::move(node));

    auto path = std::make_shared<std::vector<MaxrEngine::Vector2Df>>();
    path->push_back(labyrinth->GetCellCoordinates({3, 3}));
    path->push_back(labyrinth->GetCellCoordinates({1, 3}));
    path->push_back(labyrinth->GetCellCoordinates({1, 1}));

    BTMoveAlongPath::SetUpBlackboard(blackboard, path);
    node = BTMoveAlongPath::Create();
    root->AddChild(std::move(node));
    /*BTMoveToPoint::SetUpBlackboard(blackboard,
                                   labyrinth->GetCellCoordinates({3, 3}));
    node = std::make_unique<BTMoveToPoint>();
    root->AddChild(std::move(node));*/
}
void DevelopLevel::Restart() {
    Stop();
    Start();
}
void DevelopLevel::Stop() { MaxrEngine::GameWorld::Instance()->Clear(); }
}  // namespace Roguelike
#endif  // ROGUELIKE_DEVELOPER_LEVEL