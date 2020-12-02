#include <ui/uispritecomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void UISpriteComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["spriteSheetX"] = m_SpriteSheetX;
    j["spriteSheetY"] = m_SpriteSheetY;
    j["scaleX"] = m_ScaleX;
    j["scaleY"] = m_ScaleY;
    j["priority"] = m_Priority;
}

ironEND_NAMESPACE