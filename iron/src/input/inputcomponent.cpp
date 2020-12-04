#include <input/inputcomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void InputComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 475433204;
}

ironEND_NAMESPACE