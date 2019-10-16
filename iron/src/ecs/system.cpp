#pragma once

#include <ecs/system.h>

ironBEGIN_NAMESPACE

void System::RegisterEntity(Entity* entity)
{
	OnRegisterEntity(entity);
}

ironEND_NAMESPACE