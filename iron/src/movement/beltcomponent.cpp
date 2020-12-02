#include <movement/beltcomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void BeltComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["speed"] = m_Speed;
    JSON directionJson;
    nlohmann::json& directionJ = directionJson.GetJ();
    directionJ["x"] = m_Direction.GetX();
    directionJ["y"] = m_Direction.GetY();
    j["direction"] = directionJ;
}

ironEND_NAMESPACE