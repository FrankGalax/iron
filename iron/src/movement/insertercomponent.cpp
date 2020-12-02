#include <movement/insertercomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void InserterComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE