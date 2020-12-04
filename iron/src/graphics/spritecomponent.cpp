#include <graphics/spritecomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void SpriteComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 1309780063;
    j["spriteSheetX"] = m_SpriteSheetX;
    j["spriteSheetY"] = m_SpriteSheetY;
    j["scaleX"] = m_ScaleX;
    j["scaleY"] = m_ScaleY;
    j["rotation"] = m_Rotation;
    j["priority"] = m_Priority;
}

ironEND_NAMESPACE