#include <input/inputcomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void InputComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = -1831897379;
}

void InputComponent::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

void InputComponent::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE