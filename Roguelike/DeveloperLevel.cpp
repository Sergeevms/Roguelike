#include "DeveloperLevel.h"
#include "GameWorld.h"
#include "Settings.h"
#include "LabyrinthBuilder.h"
#include "AITargetSearchComponent.h"
#include "AIChaseTargetComponent.h"

namespace Roguelike
{
    void DeveloperLevel::Start() 
    {
        auto settings = Settings::Instance();
        LabyrinthBuilder labyrinthBuilder;
        labyrinthBuilder.StartBuilding({ 30, 30 });
        labyrinthBuilder.AddRect({ 10, 10 }, { 20, 20 });
        labyrinthBuilder.AddRect({ 0, 0 }, { 20, 20 });
        for (int i = 0; i < 10; ++i)
        {
            labyrinthBuilder.SetWall({20, 10 + i});
        }        
        labyrinth = labyrinthBuilder.ConstructLabyrinth();
        player = std::make_shared<Player>();        
        backgroundMusic = std::make_shared<BackgroundMusic>();
        enemy = std::make_shared<Enemy>();
        
        auto enemyTransform = enemy->GetGameObject()->GetComponent<MaxrEngine::TransformComponent>();
        enemyTransform->SetWorldPosition({ 7.f * settings->playerSize, 7.f * settings->playerSize });
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