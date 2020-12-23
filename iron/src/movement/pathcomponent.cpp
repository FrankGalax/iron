#include <movement/pathcomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void PathComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = -639674736;
    JSON targetJson;
    nlohmann::json& targetJ = targetJson.GetJ();
    targetJ["x"] = m_Target.GetX();
    targetJ["y"] = m_Target.GetY();
    j["target"] = targetJ;
}

void PathComponent::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    m_Target = Vector2f(j["target"]["x"], j["target"]["y"]);
}

void PathComponent::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE