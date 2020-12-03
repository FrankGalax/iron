#include <item/resourcecomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void ResourceComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["resourceType"] = (int)m_ResourceType;
}

ironEND_NAMESPACE