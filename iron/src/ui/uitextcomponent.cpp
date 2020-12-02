#include <ui/uitextcomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void UITextComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["string"] = m_String;
    j["size"] = m_Size;
}

ironEND_NAMESPACE