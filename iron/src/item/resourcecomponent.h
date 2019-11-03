#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <item/itemenum.h>

ironBEGIN_NAMESPACE

class ResourceComponent : public Component
{
public:
	ResourceComponent(ResourceType resourceType) : m_ResourceType(resourceType) {}

	ResourceType GetResourceType() const { return m_ResourceType; }

private:
	ResourceType m_ResourceType;
};

ironEND_NAMESPACE