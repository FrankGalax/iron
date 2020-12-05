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
    nlohmann::json& j = json->GetJ();
    m_Position = Vector2f(j["position"]["x"], j["position"]["y"]);
    m_Size = Vector2f(j["size"]["x"], j["size"]["y"]);
}

void PositionComponent::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE