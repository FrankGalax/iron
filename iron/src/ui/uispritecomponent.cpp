#include <ui/uispritecomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void UISpriteComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = -651037376;
    j["spriteSheetX"] = m_SpriteSheetX;
    j["spriteSheetY"] = m_SpriteSheetY;
    j["scaleX"] = m_ScaleX;
    j["scaleY"] = m_ScaleY;
    j["priority"] = m_Priority;
}

void UISpriteComponent::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    m_SpriteSheetX = j["spriteSheetX"];
    m_SpriteSheetY = j["spriteSheetY"];
    m_ScaleX = j["scaleX"];
    m_ScaleY = j["scaleY"];
    m_Priority = j["priority"];
}

void UISpriteComponent::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE