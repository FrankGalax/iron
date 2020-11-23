#include <movement/beltsystem.h>
#include <movement/beltcomponent.h>
#include <movement/onbeltcomponent.h>
#include <movement/positioncomponent.h>
#include <utils.h>
#include <assert.h>
#include <iostream>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2(BeltSystem, BeltSystemTuple, OnBeltComponent, PositionComponent)

void BeltSystem::Update(float deltaTime)
{
    for (BeltSystemTuple& tuple : m_Tuples)
    {
        if (const BeltComponent* belt = tuple.m_OnBeltComponent->GetBelt())
        {
            Vector2f& position = tuple.m_PositionComponent->GetPosition();

            if (belt->GetNextBelt() == nullptr)
            {
                std::vector<Entity*> entities;
                Utils::GetEntitiesAtPosition(belt->GetOwner()->GetWorld(), position + belt->GetDirection(), entities);
                if (!entities.empty())
                {
                    return;
                }
            }

            position += belt->GetDirection() * belt->GetSpeed() * deltaTime;

            Vector2f testPosition;
            const Vector2f& beltPosition = belt->GetOwner()->GetPositionComponent()->GetPosition();
            
            if (belt->GetDirection().Equals(Vector2f::Right))
            {
                position.SetY(beltPosition.GetY());
                testPosition = position;
            }
            else if (belt->GetDirection().Equals(Vector2f::Down))
            {
                position.SetX(beltPosition.GetX());
                testPosition = position;
            }
            else if (belt->GetDirection().Equals(Vector2f::Left))
            {
                position.SetY(beltPosition.GetY());
                testPosition = position;
                testPosition.SetX(testPosition.GetX() + 1.f);
            }
            else if (belt->GetDirection().Equals(Vector2f::Up))
            {
                position.SetX(beltPosition.GetX());
                testPosition = position;
                testPosition.SetY(testPosition.GetY() + 1.f);
            }

            if (!Utils::IsColliding(belt->GetOwner()->GetPositionComponent(), testPosition))
            {
                const BeltComponent* nextBelt = belt->GetNextBelt();
                tuple.m_OnBeltComponent->SetBelt(nextBelt);
            }
        }
    }
}

ironEND_NAMESPACE