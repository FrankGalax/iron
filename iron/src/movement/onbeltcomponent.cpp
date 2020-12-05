#include <movement/onbeltcomponent.h>
#include <json.h>

#pragma region usercode
#include <ecs/entity.h>
#include <movement/beltcomponent.h>
#pragma endregion

ironBEGIN_NAMESPACE

void OnBeltComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 2124386125;
    JSON beltJson;
    nlohmann::json& beltJ = beltJson.GetJ();
    const int beltEntityId = m_Belt != nullptr ? m_Belt->GetOwner()->GetId() : -1;
    beltJ["entityId"] = beltEntityId;
    beltJ["class"] = 817766642;
    j["belt"] = beltJ;
}

void OnBeltComponent::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

void OnBeltComponent::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE