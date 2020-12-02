#include <movement/onbeltcomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void OnBeltComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE