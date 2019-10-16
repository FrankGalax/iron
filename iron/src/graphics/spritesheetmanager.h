#pragma once

#include <iron.h>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

class SpriteSheetManager
{
public:
    static SpriteSheetManager& GetInstance()
    {
        static SpriteSheetManager instance;
        return instance;
    }

    SpriteSheetManager(const SpriteSheetManager& other) = delete;
    void operator=(const SpriteSheetManager& other) = delete;
private:
    SpriteSheetManager() {}

public:
    void LoadSpriteSheet();


private:
    sf::Texture m_SpriteSheet;
};

ironEND_NAMESPACE