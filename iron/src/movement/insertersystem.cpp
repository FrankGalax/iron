#include <movement/insertersystem.h>
#include <data/entitybuilder.h>
#include <ecs/world.h>
#include <item/craftercomponent.h>
#include <item/resourcecomponent.h>
#include <item/inventorycomponent.h>
#include <movement/beltcomponent.h>
#include <movement/onbeltcomponent.h>
#include <movement/positioncomponent.h>
#include <movement/insertercomponent.h>
#include <utils.h>

#include <iostream>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2_3(InserterSystem, InserterSystemTuple, InserterComponent, PositionComponent, ResourceComponent, InventoryComponent, BeltComponent)

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
			if (inserter->m_InserterComponent->GetIn() == nullptr && !insertable->m_InserterComponent->GetIsInsertableOutOnly())
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
            if (outInsertable->m_InventoryComponent != nullptr)
            {
                if (inInsertable->m_ResourceComponent != nullptr)
                {
                    std::vector<InventoryItem>& pendingAddItems = outInsertable->m_InventoryComponent->GetPendingAddItems();
                    pendingAddItems.push_back(InventoryItem(inInsertable->m_ResourceComponent->GetResourceType()));
                    inserter->m_InserterComponent->SetIn(nullptr);
                    inserter->m_InserterComponent->SetOut(nullptr);
                    inInsertable->m_Entity->GetWorld()->RemoveEntity(inInsertable->m_Entity);

                    std::cout << "insert " << inInsertable->m_Entity->GetName().c_str() << " into " << outInsertable->m_Entity->GetName().c_str() << std::endl;
                }
                else if (inInsertable->m_InventoryComponent != nullptr)
                {
                    std::vector<InventoryItem>& inInventoryItems = inInsertable->m_InventoryComponent->GetItems();
                    if (!inInventoryItems.empty() && inInventoryItems[0].m_IsOutput)
                    {
                        std::vector<InventoryItem>& pendingAddItems = outInsertable->m_InventoryComponent->GetPendingAddItems();
                        pendingAddItems.push_back(inInventoryItems[0]);

                        std::vector<InventoryItem>& pendingRemoveItems = inInsertable->m_InventoryComponent->GetPendingRemoveItems();
                        pendingRemoveItems.push_back(inInventoryItems[0]);

                        inserter->m_InserterComponent->SetIn(nullptr);
                        inserter->m_InserterComponent->SetOut(nullptr);

                        std::cout << "insert " << inInsertable->m_Entity->GetName().c_str() << " into " << outInsertable->m_Entity->GetName().c_str() << std::endl;
                    }
                }
            }
            else if (outInsertable->m_BeltComponent != nullptr)
            {
                if (inInsertable->m_ResourceComponent != nullptr)
                {

                }
                else if (inInsertable->m_InventoryComponent != nullptr)
                {
                    std::vector<InventoryItem>& inInventoryItems = inInsertable->m_InventoryComponent->GetItems();
                    if (!inInventoryItems.empty() && inInventoryItems[0].m_IsOutput)
                    {
                        InventoryItem& inventoryItem = inInventoryItems[0];

                        World* world = inInsertable->m_Entity->GetWorld();
                        Entity* entity = world->CreateEntity();
                        EntityBuilder::BuildFromResource(entity, outInsertable->m_PositionComponent->GetPosition(), inventoryItem.m_ResourceType);

                        OnBeltComponent* onBeltComponent = new OnBeltComponent();
                        onBeltComponent->SetBelt(outInsertable->m_BeltComponent);
                        entity->AddComponent(onBeltComponent);

                        world->AddEntity(entity);

                        inInsertable->m_InventoryComponent->GetPendingRemoveItems().push_back(inventoryItem);

                        inserter->m_InserterComponent->SetIn(nullptr);
                        inserter->m_InserterComponent->SetOut(nullptr);

                        std::cout << "insert " << entity->GetName().c_str() << " onto belt" << std::endl;
                    }
                }
            }
        }
            
    }
}

ironEND_NAMESPACE