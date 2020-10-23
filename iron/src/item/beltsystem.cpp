#include <item/beltsystem.h>
#include <item/beltcomponent.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_1(BeltSystem, BeltSystemTuple, BeltComponent)

void BeltSystem::Update(float deltaTime)
{
    for (BeltSystemTuple& tuple : m_Tuples)
    {

    }
}

ironEND_NAMESPACE