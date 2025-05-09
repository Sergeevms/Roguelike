#include "DeveloperLevel.h"
#include "GameWorld.h"
#include "Settings.h"
#include "LabyrinthBuilder.h"
#include "AIInputComponent.h"

namespace Roguelike
{
    void DeveloperLevel::Start() 
    {
        auto settings = Settings::Instance();
        LabyrinthBuilder labyrinthBuilder;
        labyrinthBuilder.StartBuilding({ 20, 20 });
        labyrinthBuilder.AddRect({ 5, 5 }, { 15, 15 });
        labyrinthBuilder.AddRect({ 0, 0 }, { 15,15 });
        labyrinth = labyrinthBuilder.ConstructLabyrinth();
        player = std::make_shared<Player>();        
        backgroundMusic = std::make_shared<BackgroundMusic>();
        enemy = std::make_shared<Enemy>();
        auto playerTransform = player->GetGameObject()->GetComponent<MaxrEngine::TransformComponent>();
        auto enemyMovement = enemy->GetGameObject()->GetComponent<MaxrEngine::AIInputComponent>();
        enemyMovement->SetTargetLocation(playerTransform->GetWorldPosition());
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