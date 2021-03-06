#pragma once

#include <iron.h>
#include <ecs/component.h>

#pragma region usercode
#include <graphics/spriteinfo.h>
#include <SFML/Graphics.hpp>
#pragma endregion

ironBEGIN_NAMESPACE

class JSON;

class SpriteComponent : public Component
{
public:
    SpriteComponent() {}
    SpriteComponent(int spriteSheetX, int spriteSheetY, float scaleX, float scaleY, float rotation, int priority) : m_SpriteSheetX(spriteSheetX), m_SpriteSheetY(spriteSheetY), m_ScaleX(scaleX), m_ScaleY(scaleY), m_Rotation(rotation), m_Priority(priority) {}

    int GetSpriteSheetX() const { return m_SpriteSheetX; }
    void SetSpriteSheetX(int spriteSheetX) { m_SpriteSheetX = spriteSheetX; }
    int GetSpriteSheetY() const { return m_SpriteSheetY; }
    void SetSpriteSheetY(int spriteSheetY) { m_SpriteSheetY = spriteSheetY; }
    float GetScaleX() const { return m_ScaleX; }
    float GetScaleY() const { return m_ScaleY; }
    float GetRotation() const { return m_Rotation; }
    int GetPriority() const { return m_Priority; }

    virtual void ToJSON(JSON* j) override;
    virtual void FromJSON(JSON* j) override;
    virtual void FromJSONResolve(JSON* j) override;

private:
    int m_SpriteSheetX = 0;
    int m_SpriteSheetY = 0;
    float m_ScaleX = 0.f;
    float m_ScaleY = 0.f;
    float m_Rotation = 0.f;
    int m_Priority = 0;

#pragma region usercodeclass
public:
    SpriteComponent(const SpriteInfo& spriteInfo) :
        m_SpriteSheetX(spriteInfo.m_SpriteSheetX), m_SpriteSheetY(spriteInfo.m_SpriteSheetY), m_ScaleX(spriteInfo.m_ScaleX),
        m_ScaleY(spriteInfo.m_ScaleY), m_Rotation(spriteInfo.m_Rotation), m_Priority(spriteInfo.m_Priority) {}

    const sf::Sprite& GetSprite() const { return m_Sprite; }
    sf::Sprite& GetSprite() { return m_Sprite; }

private:
    sf::Sprite m_Sprite;
#pragma endregion
};

ironEND_NAMESPACE