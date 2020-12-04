#include <ecs/component.h>
#include <json.h>

ironBEGIN_NAMESPACE

void Component::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 1726162492;
}

ironEND_NAMESPACE