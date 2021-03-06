#include <movement/insertercomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void InserterComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 570334859;
    j["inserterType"] = (int)m_InserterType;
    JSON inOffsetJson;
    nlohmann::json& inOffsetJ = inOffsetJson.GetJ();
    inOffsetJ["x"] = m_InOffset.GetX();
    inOffsetJ["y"] = m_InOffset.GetY();
    j["inOffset"] = inOffsetJ;
    JSON outOffsetJson;
    nlohmann::json& outOffsetJ = outOffsetJson.GetJ();
    outOffsetJ["x"] = m_OutOffset.GetX();
    outOffsetJ["y"] = m_OutOffset.GetY();
    j["outOffset"] = outOffsetJ;
    j["isInsertableOutOnly"] = m_IsInsertableOutOnly;
}

void InserterComponent::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    m_InserterType = static_cast<InserterType>(j["inserterType"]);
    m_InOffset = Vector2f(j["inOffset"]["x"], j["inOffset"]["y"]);
    m_OutOffset = Vector2f(j["outOffset"]["x"], j["outOffset"]["y"]);
    m_IsInsertableOutOnly = j["isInsertableOutOnly"];
}

void InserterComponent::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE