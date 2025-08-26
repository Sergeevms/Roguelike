#ifdef CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
#define NOMINMAX
#include <Windows.h>  //NOLINT(misc-include-cleaner) : system specific header
#include <stdio.h>
#endif  // CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT

#include <memory>

// #include "DeveloperLevel.h"
#include "Engine.h"
#include "GameLevel.h"
#include "LevelManager.h"
#include "Logger.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "Settings.h"

int main() {
    const std::shared_ptr<MaxrEngine::Logger> globalLogger =
        std::make_shared<MaxrEngine::Logger>();
    MaxrEngine::LoggerRegister::GetInstance().RegisterLogger("Global",
                                                             globalLogger);
#ifdef CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
    AllocConsole();  // NOLINT(misc-include-cleaner)
    FILE* console;
    freopen_s(&console, "CONOUT$", "w", stdout);
    globalLogger->AddSink(std::make_shared<MaxrEngine::ConsoleSink>());
#endif  // CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
    // globalLogger->AddSink(std::make_shared<MaxrEngine::FileSink>("Log.txt"));

    globalLogger->SetLoggedLevels(MaxrEngine::LogLevel::ALL);
    LOG_INFO("ProgramStarted");

    auto* settings = Roguelike::Settings::Instance();

    MaxrEngine::RenderSystem::Instance()->CrateMainWindow(
        sf::VideoMode(settings->screenWidth, settings->screenHeight),
        settings->gameName);

    MaxrEngine::ResourceSystem::Instance()->LoadTextureMap(
        settings->playerTextureMap);
    MaxrEngine::ResourceSystem::Instance()->LoadTextureMap(
        settings->enemyTextureMap);
    MaxrEngine::ResourceSystem::Instance()->LoadTextureMap(
        settings->wallTextureMap);
    MaxrEngine::ResourceSystem::Instance()->LoadTextureMap(
        settings->floorTextureMap);

    MaxrEngine::ResourceSystem::Instance()->LoadMusic(
        "background",
        settings->soundPath + "Clinthammer__Background_Music.wav");
    MaxrEngine::ResourceSystem::Instance()->LoadFont(
        "default", settings->fontPath + "Roboto-Regular.ttf");

    Roguelike::LevelManager::Instance()->RegisterLevel(
        std::make_unique<Roguelike::GameLevel>(settings->firstLevelParameters));
    ;
    auto param = settings->firstLevelParameters;
    param.builderParameters.width += 8;
    param.builderParameters.heigth += 4;
    Roguelike::LevelManager::Instance()->RegisterLevel(
        std::make_unique<Roguelike::GameLevel>(param));
    ;
    Roguelike::LevelManager::Instance()->LoadNextLevel();
    MaxrEngine::Engine::Instance()->Run();

    return 0;
}
