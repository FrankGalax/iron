#include <ecs/component.h>
#include <json.h>

ironBEGIN_NAMESPACE

void Component::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 1948514967;
}

ironEND_NAMESPACE