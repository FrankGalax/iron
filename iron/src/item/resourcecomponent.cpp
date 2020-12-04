#include <item/resourcecomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void ResourceComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = -524183048;
    j["resourceType"] = (int)m_ResourceType;
}

ironEND_NAMESPACE