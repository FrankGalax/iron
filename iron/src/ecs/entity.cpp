#include <ecs/entity.h>
#include <json.h>

#pragma region usercode
#include <ecs/component.h>
#include <movement/positioncomponent.h>
#pragma endregion

ironBEGIN_NAMESPACE

void Entity::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["id"] = m_Id;
    j["name"] = m_Name;
    for (Component* component : m_Components)
    {
        JSON subJSON;
        component->ToJSON(&subJSON);
        j["components"].push_back(subJSON.GetJ());
    }
}

#pragma region usercodenamespace
Entity::~Entity()
{
    for (Component* component : m_Components)
    {
        delete component;
    }
}

void Entity::AddComponent(Component* component)
{
    if (component != nullptr)
    {
        component->SetOwner(this);
        m_Components.push_back(component);
    }
}

void Entity::ResetComponentCaches()
{
    m_PositionComponentCache.Reset();
}

PositionComponent* Entity::GetPositionComponent()
{
    return m_PositionComponentCache.GetComponent(this);
}

const PositionComponent* Entity::GetPositionComponent() const
{
    return m_PositionComponentCache.GetComponent(this);
}
#pragma endregion

ironEND_NAMESPACE