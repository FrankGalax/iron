#include <movement/insertersystem.h>
#include <movement/positioncomponent.h>
#include <movement/insertercomponent.h>
#include <utils.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2(InserterSystem, InserterSystemTuple, InserterComponent, PositionComponent)

void InserterSystem::Update(float deltaTime)
{
    std::vector<InserterSystemTuple*> insertables;
    std::vector<InserterSystemTuple*> inserters;

    for (InserterSystemTuple& tuple : m_Tuples)
    {
        if (tuple.m_InserterComponent->GetInserterType() == InserterComponent::InserterType::Insertable)
        {
            insertables.push_back(&tuple);
        }
        else
        {
            inserters.push_back(&tuple);
        }
    }

    for (InserterSystemTuple* inserter : inserters)
    {
        for (InserterSystemTuple* insertable : insertables)
		{
			if (inserter->m_InserterComponent->GetIn() == nullptr)
			{
				const Vector2f testPosition = inserter->m_PositionComponent->GetPosition() + inserter->m_InserterComponent->GetInOffset();
				if (Utils::IsColliding(insertable->m_PositionComponent, testPosition))
				{
					inserter->m_InserterComponent->SetIn(insertable->m_Entity);
				}
			}

			if (inserter->m_InserterComponent->GetOut() == nullptr)
			{
				const Vector2f testPosition = inserter->m_PositionComponent->GetPosition() + inserter->m_InserterComponent->GetOutOffset();
				if (Utils::IsColliding(insertable->m_PositionComponent, testPosition))
				{
					inserter->m_InserterComponent->SetOut(insertable->m_Entity);
				}
			}
        }
    }
}

ironEND_NAMESPACE