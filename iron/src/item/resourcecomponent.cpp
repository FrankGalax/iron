#include <item/resourcecomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void ResourceComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 1835672005;
    j["resourceType"] = (int)m_ResourceType;
}

void ResourceComponent::FromJSON(JSON* json)
{
}

ironEND_NAMESPACE