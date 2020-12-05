#include <graphics/spritecomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void SpriteComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = -120479234;
    j["spriteSheetX"] = m_SpriteSheetX;
    j["spriteSheetY"] = m_SpriteSheetY;
    j["scaleX"] = m_ScaleX;
    j["scaleY"] = m_ScaleY;
    j["rotation"] = m_Rotation;
    j["priority"] = m_Priority;
}

void SpriteComponent::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    m_SpriteSheetX = j["spriteSheetX"];
    m_SpriteSheetY = j["spriteSheetY"];
    m_ScaleX = j["scaleX"];
    m_ScaleY = j["scaleY"];
    m_Rotation = j["rotation"];
    m_Priority = j["priority"];
}

void SpriteComponent::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE