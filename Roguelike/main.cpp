#ifdef CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
#define NOMINMAX
#include <Windows.h>
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
    AllocConsole();
    FILE* console;
    freopen_s(&console, "CONOUT$", "w", stdout);
    globalLogger->AddSink(std::make_shared<MaxrEngine::ConsoleSink>());
#endif  // CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
    globalLogger->AddSink(std::make_shared<MaxrEngine::FileSink>("Log.txt"));
    globalLogger->SetLoggedLevels(MaxrEngine::LogLevel::ALL);
    LOG_INFO("ProgramStarted");
    auto* settings = Roguelike::Settings::Instance();
    MaxrEngine::RenderSystem::Instance()->CrateMainWindow(
        sf::VideoMode(settings->screenWidth, settings->screenHeight),
        settings->gameName);

    MaxrEngine::ResourceSystem::Instance()->LoadTextureMap(
        "PlayerTextures", settings->textureMapsPath + "Player.png", {48, 63}, 9,
        false);
    MaxrEngine::ResourceSystem::Instance()->LoadTextureMap(
        "WallTextures", settings->textureMapsPath + "Wall.png", {16, 16}, 48,
        false);
    MaxrEngine::ResourceSystem::Instance()->LoadTextureMap(
        "FloorTextures", settings->textureMapsPath + "Floor.png", {16, 16}, 49,
        false);

    MaxrEngine::ResourceSystem::Instance()->LoadTexture(
        "Ball", settings->texturePath + "Ball.png", false);
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
