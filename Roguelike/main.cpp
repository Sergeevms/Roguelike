#ifdef CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
#define NOMINMAX
#include <Windows.h>  //NOLINT(misc-include-cleaner) : system specific header
#include <stdio.h>
#endif  // CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT

#include <memory>

#include "DeveloperLevel.h"
#include "Engine.h"
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
    MaxrEngine::RenderSystem::Instance()->SetUpLayers(
        static_cast<int>(Roguelike::Settings::RenderLayers::Count));
    MaxrEngine::RenderSystem::LayerBitmask activeLayers;
#ifdef NDEBUG
    activeLayers.SetLayerValue(
        static_cast<int>(Roguelike::Settings::RenderLayers::Debug), false);
#endif  // NDEBUG

    MaxrEngine::RenderSystem::Instance()->SetActiveLayers(activeLayers);

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

    auto developerLevel = std::make_shared<Roguelike::DeveloperLevel>();
    developerLevel->Start();
    MaxrEngine::Engine::Instance()->Run();
    developerLevel->Stop();

    return 0;
}
