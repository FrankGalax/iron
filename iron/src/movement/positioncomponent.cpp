#include <movement/positioncomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void PositionComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE