#include <ecs/component.h>
#include <json.h>

ironBEGIN_NAMESPACE

void Component::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE