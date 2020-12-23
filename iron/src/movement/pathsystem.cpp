#include <movement/pathsystem.h>
#include <movement/pathcomponent.h>
#include <movement/positioncomponent.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2(PathSystem, PathSystemTuple, PathComponent, PositionComponent);

void PathSystem::Update(float deltaTime)
{
    for (PathSystemTuple& tuple : m_Tuples)
    {

    }
}

ironEND_NAMESPACE