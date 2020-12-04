#pragma once

#include <iron.h>
#include <ecs/component.h>

#pragma region usercode
#include <item/itemenum.h>
#pragma endregion

ironBEGIN_NAMESPACE

class JSON;

class ResourceComponent : public Component
{
public:
    ResourceComponent() {}
    ResourceComponent(ResourceType resourceType) : m_ResourceType(resourceType) {}

    ResourceType GetResourceType() const { return m_ResourceType; }

    virtual void ToJSON(JSON* j) override;

private:
    ResourceType m_ResourceType = ResourceType::None;
};

ironEND_NAMESPACE