#pragma once

#include <iron.h>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

class SpriteSheetManager
{
public:
	SpriteSheetManager() {}
	~SpriteSheetManager() {}
	SpriteSheetManager(const SpriteSheetManager& other) = delete;
	SpriteSheetManager& operator=(const SpriteSheetManager& other) = delete;

    void LoadSpriteSheet();
	const sf::Texture& GetSpriteSheet() const { return m_SpriteSheet; }

private:
    sf::Texture m_SpriteSheet;
};

ironEND_NAMESPACE