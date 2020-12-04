#pragma once

#include <iron.h>

ironBEGIN_NAMESPACE

class JSON;

class AnimationSprite
{
public:
    AnimationSprite() {}
    AnimationSprite(int spriteSheetX, int spriteSheetY) : m_SpriteSheetX(spriteSheetX), m_SpriteSheetY(spriteSheetY) {}

    int GetSpriteSheetX() const { return m_SpriteSheetX; }
    void SetSpriteSheetX(int spriteSheetX) { m_SpriteSheetX = spriteSheetX; }
    int GetSpriteSheetY() const { return m_SpriteSheetY; }
    void SetSpriteSheetY(int spriteSheetY) { m_SpriteSheetY = spriteSheetY; }

    void ToJSON(JSON* j);

private:
    int m_SpriteSheetX = 0;
    int m_SpriteSheetY = 0;

#pragma region usercodeclass
public:
    void SetSpriteSheetXY(int spriteSheetX, int spriteSheetY) { m_SpriteSheetX = spriteSheetX; m_SpriteSheetY = spriteSheetY; }
#pragma endregion
};

ironEND_NAMESPACE