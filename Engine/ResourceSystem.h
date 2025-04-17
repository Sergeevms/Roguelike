#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "EngineAPI.h"

namespace MaxrEngine
{
	class ResourceSystem
	{
	public:
		ENGINE_API static ResourceSystem* Instance();

		ENGINE_API void LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth = true);
		ENGINE_API const sf::Texture* GetTextureShared(const std::string& name) const;
		ENGINE_API sf::Texture* GetTectureCopy(const std::string& name) const;
		ENGINE_API void DeleteSharedTexture(const std::string& name);

		ENGINE_API void LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize,
			int totalElements, bool isSmooth = true);
		ENGINE_API const sf::Texture* GetTextureMapElementShared(const std::string& name, int elementIndex) const;
		ENGINE_API sf::Texture* GetTextureMapElementCopy(const std::string& name, int elementIndex) const;
		ENGINE_API int GetTextureMapElementsCount(const std::string& name) const;
		ENGINE_API void DeleteSharedTextureMap(const std::string& name);

		ENGINE_API void Clear();

	private:
		std::map<std::string, sf::Texture*> textures;
		std::map<std::string, std::vector<sf::Texture*>> textureMaps;

		ResourceSystem() {};
		~ResourceSystem() {};

		ResourceSystem(ResourceSystem const&) = delete;
		ResourceSystem& operator= (ResourceSystem const&) = delete;

		void DeleteAllTextures();
		void DeleteAllTextureMaps();
	};
}

