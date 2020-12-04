#include <movement/insertercomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void InserterComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 1842238107;
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

ironEND_NAMESPACE