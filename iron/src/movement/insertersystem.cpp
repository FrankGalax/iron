#include <movement/insertersystem.h>
#include <item/craftercomponent.h>
#include <item/resourcecomponent.h>
#include <item/inventorycomponent.h>
#include <movement/positioncomponent.h>
#include <movement/insertercomponent.h>
#include <utils.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2_3(InserterSystem, InserterSystemTuple, InserterComponent, PositionComponent, CrafterComponent, ResourceComponent, InventoryComponent)

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
        InserterSystemTuple* inInsertable = nullptr;
        InserterSystemTuple* outInsertable = nullptr;

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
                    outInsertable = insertable;
				}
			}

            if (inserter->m_InserterComponent->GetIn() == insertable->m_Entity)
            {
                inInsertable = insertable;
            }

            if (inserter->m_InserterComponent->GetOut() == insertable->m_Entity)
            {
                outInsertable = insertable;
            }
        }

        if (inInsertable != nullptr && outInsertable != nullptr)
        {
            if (inInsertable->m_ResourceComponent != nullptr &&
                outInsertable->m_CrafterComponent != nullptr &&
                outInsertable->m_CrafterComponent->GetPendingAddItem() == ResourceType::None &&
                outInsertable->m_InventoryComponent != nullptr)
            {
                outInsertable->m_CrafterComponent->SetPendingAddItem(inInsertable->m_ResourceComponent->GetResourceType());
                outInsertable->m_CrafterComponent->SetPendingAddItemAccepted(false);
            }

            if (outInsertable->m_CrafterComponent != nullptr && 
                outInsertable->m_CrafterComponent->GetPendingAddItemAccepted() &&
                outInsertable->m_InventoryComponent != nullptr &&
                inInsertable->m_ResourceComponent != nullptr)
            {
                outInsertable->m_InventoryComponent->SetPendingAddItem(inInsertable->m_ResourceComponent->GetResourceType());
                outInsertable->m_CrafterComponent->SetPendingAddItem(ResourceType::None);
                outInsertable->m_CrafterComponent->SetPendingAddItemAccepted(false);
                inserter->m_InserterComponent->SetIn(nullptr);
                inserter->m_InserterComponent->SetOut(nullptr);
                inInsertable->m_Entity->RemoveFromWorld();
            }
        }
            
    }
}

ironEND_NAMESPACE