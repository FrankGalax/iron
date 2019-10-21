#pragma once

#include <iron.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

class PositionNotifyComponent : public Component
{
public:
    enum class NotifyType
    {
        Notifier,
        Listener
    };

    PositionNotifyComponent(NotifyType notifyType) : PositionNotifyComponent(notifyType, Vector2f::Zero, Vector2f::Zero)
    {}

    PositionNotifyComponent(NotifyType notifyType, const Vector2f& inOffset, const Vector2f& outOffset) : 
        m_NotifyType(notifyType), 
        m_In(nullptr), 
        m_Out(nullptr),
        m_InOffset(inOffset),
        m_OutOffset(outOffset)
    {}

    NotifyType GetNotifyType() const { return m_NotifyType; }
    void SetIn(Entity* in) { m_In = in; }
    void SetOut(Entity* out) { m_Out = out; }

private:
    NotifyType m_NotifyType;
    Entity* m_In;
    Entity* m_Out;
    Vector2f m_InOffset;
    Vector2f m_OutOffset;
};

ironEND_NAMESPACE