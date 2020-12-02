#include <movement/beltcomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void BeltComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE