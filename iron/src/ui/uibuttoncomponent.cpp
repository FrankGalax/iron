#include <ui/uibuttoncomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void UIButtonComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = -38539479;
    j["buttonType"] = (int)m_ButtonType;
}

ironEND_NAMESPACE