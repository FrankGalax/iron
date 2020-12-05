#include <ui/uibuttoncomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void UIButtonComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 164764677;
    j["buttonType"] = (int)m_ButtonType;
}

void UIButtonComponent::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    m_ButtonType = static_cast<ButtonType>(j["buttonType"]);
}

void UIButtonComponent::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE