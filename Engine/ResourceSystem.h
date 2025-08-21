#pragma once
#include <map>
#include <string>
#include <vector>

#include "SFML/Audio/Music.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace MaxrEngine {
class ResourceSystem {
   public:
    struct TextureMapLoadingParameters {
        std::string name;
        std::string sourcePath;
        sf::Vector2i elementPixelSize;
        int totalElements;
        bool isSmooth = true;
    };
    static ResourceSystem* Instance();

    void LoadTexture(const std::string& name, std::string sourcePath,
                     bool isSmooth = true);
    const sf::Texture* GetTextureShared(const std::string& name) const;
    sf::Texture* GetTectureCopy(const std::string& name) const;
    void DeleteSharedTexture(const std::string& name);

    void LoadTextureMap(const std::string& name, std::string sourcePath,
                        sf::Vector2i elementPixelSize, int totalElements,
                        bool isSmooth = true);
    void LoadTextureMap(const TextureMapLoadingParameters& parameters);
    const sf::Texture* GetTextureMapElementShared(const std::string& name,
                                                  int elementIndex) const;
    sf::Texture* GetTextureMapElementCopy(const std::string& name,
                                          int elementIndex) const;
    int GetTextureMapElementsCount(const std::string& name) const;
    void DeleteSharedTextureMap(const std::string& name);

    void LoadSound(const std::string& name, std::string sourcePath);
    const sf::SoundBuffer* GetSoundShared(const std::string& name) const;
    sf::SoundBuffer* GetSoundCopy(const std::string& name) const;
    void DeleteSound(const std::string& name);

    void LoadFont(const std::string& name, std::string sourcePath);
    const sf::Font* GetFontShared(const std::string& name) const;
    sf::Font* GetFontCopy(const std::string& name) const;
    void DeleteFont(const std::string& name);

    void LoadMusic(const std::string& name, std::string sourcePath);
    sf::Music* GetMusicShared(const std::string& name) const;
    void DeleteMusic(const std::string& name);

    void Clear();

   private:
    std::map<std::string, sf::Texture*> textures;
    std::map<std::string, std::vector<sf::Texture*>> textureMaps;
    std::map<std::string, sf::SoundBuffer*> soundBuffers;
    std::map<std::string, sf::Music*> musics;
    std::map<std::string, sf::Font*> fonts;

    ResourceSystem() {};
    ~ResourceSystem() {};

    ResourceSystem(ResourceSystem const&) = delete;
    ResourceSystem& operator=(ResourceSystem const&) = delete;

    void DeleteAllTextures();
    void DeleteAllTextureMaps();
    void DeleteAllSounds();
    void DeleteAllMusics();
    void DeleteAllFonts();
};
}  // namespace MaxrEngine
