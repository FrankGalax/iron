#include <movement/moverightsystem.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_1(MoveRightSystem, MoveRightSystemTuple, PositionComponent)

void MoveRightSystem::Update(float deltaTime)
{
	for (MoveRightSystemTuple& tuple : m_Tuples) 
	{
		tuple.m_PositionComponent->SetX(tuple.m_PositionComponent->GetX() + 50.f * deltaTime);
	}
}

ironEND_NAMESPACE