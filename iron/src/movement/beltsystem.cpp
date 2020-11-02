#include <movement/beltsystem.h>
#include <movement/beltcomponent.h>
#include <movement/onbeltcomponent.h>
#include <movement/positioncomponent.h>
#include <utils.h>
#include <assert.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2(BeltSystem, BeltSystemTuple, OnBeltComponent, PositionComponent)

void BeltSystem::Update(float deltaTime)
{
    for (BeltSystemTuple& tuple : m_Tuples)
    {
        if (const BeltComponent* belt = tuple.m_OnBeltComponent->GetBelt())
        {
            Vector2f& position = tuple.m_PositionComponent->GetPosition();
            position += belt->GetDirection() * belt->GetSpeed() * deltaTime;

            if (!Utils::IsColliding(belt->GetOwner()->GetComponent<PositionComponent>(), position))
            {
                const BeltComponent* nextBelt = belt->GetNextBelt();
                tuple.m_OnBeltComponent->SetBelt(nextBelt);
            }
        }
    }
}

ironEND_NAMESPACE