#include <movement/positionnotifysystem.h>
#include <movement/positioncomponent.h>
#include <movement/positionnotifycomponent.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_1(PositionNotifySystem, PositionNotifySystemTuple, PositionNotifyComponent)

void PositionNotifySystem::Update(float deltaTime)
{
    std::vector<PositionNotifySystemTuple*> notifiers;
    std::vector<PositionNotifySystemTuple*> listeners;

    for (PositionNotifySystemTuple& tuple : m_Tuples)
    {
        if (tuple.m_PositionNotifyComponent->GetNotifyType() == PositionNotifyComponent::NotifyType::Notifier)
        {
            notifiers.push_back(&tuple);
        }
        else
        {
            listeners.push_back(&tuple);
        }
    }

    for (PositionNotifySystemTuple* listener : listeners)
    {
        listener->m_PositionNotifyComponent->SetIn(nullptr);
        listener->m_PositionNotifyComponent->SetOut(nullptr);

        for (PositionNotifySystemTuple* notifier : notifiers)
        {
            
        }
    }
}

ironEND_NAMESPACE