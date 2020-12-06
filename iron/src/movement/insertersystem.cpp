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
        if (tuple.m_InserterComponent->GetInserterType() == InserterType::Insertable)
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
				if (Utils::IsColliding(insertable->m_PositionComponent, testPosition, Vector2f::Zero))
				{
					inserter->m_InserterComponent->SetIn(insertable->m_Entity);
				}
			}

			if (inserter->m_InserterComponent->GetOut() == nullptr && insertable->m_Entity->GetOnBeltComponent() == nullptr)
			{
				const Vector2f testPosition = inserter->m_PositionComponent->GetPosition() + inserter->m_InserterComponent->GetOutOffset();
				if (Utils::IsColliding(insertable->m_PositionComponent, testPosition, Vector2f::Zero))
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
                    inInsertable->m_Entity->GetWorld()->DestroyEntity(inInsertable->m_Entity);

                    std::cout << "insert " << inInsertable->m_Entity->GetName().c_str() << " into " << outInsertable->m_Entity->GetName().c_str() << std::endl;
                }
                else if (inInsertable->m_InventoryComponent != nullptr)
                {
                    std::vector<InventoryItem>& inInventoryItems = inInsertable->m_InventoryComponent->GetItems();
                    if (!inInventoryItems.empty() && inInventoryItems[0].GetIsOutput())
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
                std::vector<Entity*> entitiesOnBelt;
                Utils::GetEntitiesAtPosition(outInsertable->m_Entity->GetWorld(), 
                    outInsertable->m_PositionComponent->GetPosition(), 
                    outInsertable->m_PositionComponent->GetSize(),
                    entitiesOnBelt);

                const auto iter = std::find_if(entitiesOnBelt.begin(), entitiesOnBelt.end(), [](Entity* entity)
                    {
                        return entity->GetComponent<ResourceComponent>() != nullptr;
                    });
                if (iter == entitiesOnBelt.end())
                {
                    if (inInsertable->m_ResourceComponent != nullptr)
                    {
                        World* world = inInsertable->m_Entity->GetWorld();

                        Entity* entity = world->CreateEntity();
                        EntityBuilder::BuildFromResource(entity, outInsertable->m_PositionComponent->GetPosition(),
                            inInsertable->m_ResourceComponent->GetResourceType());
                        OnBeltComponent* onBeltComponent = new OnBeltComponent();
                        onBeltComponent->SetBelt(outInsertable->m_BeltComponent);
                        entity->AddComponent(onBeltComponent);

                        world->DestroyEntity(inInsertable->m_Entity);

                        inserter->m_InserterComponent->SetIn(nullptr);
                        inserter->m_InserterComponent->SetOut(nullptr);

                        std::cout << "insert " << inInsertable->m_Entity->GetName().c_str() << " onto belt" << std::endl;
                    }
                    else if (inInsertable->m_InventoryComponent != nullptr)
                    {
                        std::vector<InventoryItem>& inInventoryItems = inInsertable->m_InventoryComponent->GetItems();
                        for (InventoryItem& inInventoryItem : inInventoryItems)
                        {
                            if (inInventoryItem.GetIsOutput())
                            {
                                World* world = inInsertable->m_Entity->GetWorld();
                                Entity* entity = world->CreateEntity();
                                EntityBuilder::BuildFromResource(entity, outInsertable->m_PositionComponent->GetPosition(), inInventoryItem.GetResourceType());

                                OnBeltComponent* onBeltComponent = new OnBeltComponent();
                                onBeltComponent->SetBelt(outInsertable->m_BeltComponent);
                                entity->AddComponent(onBeltComponent);

                                InventoryItem removeItem = inInventoryItem;
                                removeItem.SetQuantity(1);
                                inInsertable->m_InventoryComponent->GetPendingRemoveItems().push_back(removeItem);

                                inserter->m_InserterComponent->SetIn(nullptr);
                                inserter->m_InserterComponent->SetOut(nullptr);

                                std::cout << "insert " << entity->GetName().c_str() << " onto belt" << std::endl;
                                break;
                            }
                        }
                    }
                }
            }
        }
            
    }
}

ironEND_NAMESPACE