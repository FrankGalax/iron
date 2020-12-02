#include <input/inputcomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void InputComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["isLeftMouseButtonPressed"] = m_IsLeftMouseButtonPressed;
    j["wasLeftMouseButtonPressed"] = m_WasLeftMouseButtonPressed;
}

ironEND_NAMESPACE