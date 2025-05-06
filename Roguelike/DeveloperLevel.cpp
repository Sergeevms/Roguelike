#include "DeveloperLevel.h"
#include "GameWorld.h"
#include "Settings.h"
#include "LabyrinthBuilder.h"

namespace Roguelike
{
    void DeveloperLevel::Start() 
    {
        auto settings = Settings::Instance();
        LabyrinthBuilder labyrinthBuilder;
        labyrinthBuilder.StartBuilding({ 20, 20 });
        labyrinthBuilder.AddRect({ 5, 0 }, { 30, 30 });
        labyrinthBuilder.AddRect({ 0, 0 }, { 15,15 });
        labyrinth = labyrinthBuilder.ConstructLabyrinth();
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