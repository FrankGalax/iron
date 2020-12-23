#include <movement/pathtargetcomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void PathTargetComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = -1243637833;
}

void PathTargetComponent::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

void PathTargetComponent::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE