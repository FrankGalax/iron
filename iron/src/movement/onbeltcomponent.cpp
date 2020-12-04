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
    j["class"] = 1075717333;
    JSON beltJson;
    nlohmann::json& beltJ = beltJson.GetJ();
    const int beltEntityId = m_Belt != nullptr ? m_Belt->GetOwner()->GetId() : -1;
    beltJ["entityId"] = beltEntityId;
    beltJ["class"] = 1004248632;
    j["belt"] = beltJ;
}

ironEND_NAMESPACE