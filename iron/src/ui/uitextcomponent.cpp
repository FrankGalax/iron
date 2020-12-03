#include <ui/uitextcomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void UITextComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["string"] = m_String;
    JSON colorJson;
    nlohmann::json& colorJ = colorJson.GetJ();
    colorJ["r"] = m_Color.r;
    colorJ["g"] = m_Color.g;
    colorJ["b"] = m_Color.b;
    colorJ["a"] = m_Color.a;
    j["color"] = colorJ;
    j["size"] = m_Size;
}

ironEND_NAMESPACE