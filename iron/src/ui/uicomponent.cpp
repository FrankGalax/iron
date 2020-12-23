#include <ui/uicomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void UIComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = -79879393;
    j["uIState"] = (int)m_UIState;
}

void UIComponent::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    m_UIState = static_cast<UIState>(j["uIState"]);
}

void UIComponent::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE