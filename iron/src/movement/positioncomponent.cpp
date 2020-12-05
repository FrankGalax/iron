#include <movement/positioncomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void PositionComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = -110003308;
    JSON positionJson;
    nlohmann::json& positionJ = positionJson.GetJ();
    positionJ["x"] = m_Position.GetX();
    positionJ["y"] = m_Position.GetY();
    j["position"] = positionJ;
    JSON sizeJson;
    nlohmann::json& sizeJ = sizeJson.GetJ();
    sizeJ["x"] = m_Size.GetX();
    sizeJ["y"] = m_Size.GetY();
    j["size"] = sizeJ;
}

void PositionComponent::FromJSON(JSON* json)
{
}

ironEND_NAMESPACE