#include <movement/beltcomponent.h>
#include <json.h>

#pragma region usercode
#include <data/componentbuilder.h>
#include <ecs/entity.h>
#include <ecs/world.h>
#pragma endregion

ironBEGIN_NAMESPACE

void BeltComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 817766642;
    JSON nextBeltJson;
    nlohmann::json& nextBeltJ = nextBeltJson.GetJ();
    const int nextBeltEntityId = m_NextBelt != nullptr ? m_NextBelt->GetOwner()->GetId() : -1;
    nextBeltJ["entityId"] = nextBeltEntityId;
    nextBeltJ["class"] = 817766642;
    j["nextBelt"] = nextBeltJ;
    j["speed"] = m_Speed;
    JSON directionJson;
    nlohmann::json& directionJ = directionJson.GetJ();
    directionJ["x"] = m_Direction.GetX();
    directionJ["y"] = m_Direction.GetY();
    j["direction"] = directionJ;
}

void BeltComponent::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    m_Speed = j["speed"];
    m_Direction = Vector2f(j["direction"]["x"], j["direction"]["y"]);
}

void BeltComponent::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    if (Entity* nextBeltEntity = GetOwner()->GetWorld()->GetEntityById(j["nextBelt"]["entityId"]))
    {
        m_NextBelt = static_cast<BeltComponent*>(ComponentBuilder::GetComponent(nextBeltEntity, j["nextBelt"]["class"]));
    }
}

ironEND_NAMESPACE