#pragma once

#include <iron.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

class InserterComponent : public Component
{
public:
    enum class InserterType
    {
        Insertable,
        Inserter
    };

	InserterComponent(InserterType inserterType) : InserterComponent(inserterType, Vector2f::Zero, Vector2f::Zero)
    {}

	InserterComponent(InserterType inserterType, const Vector2f& inOffset, const Vector2f& outOffset) :
        m_InserterType(inserterType),
        m_In(nullptr), 
        m_Out(nullptr),
        m_InOffset(inOffset),
        m_OutOffset(outOffset),
        m_IsInsertableOutOnly(false)
    {}

    InserterType GetInserterType() const { return m_InserterType; }
    void SetIn(Entity* in) { m_In = in; }
	const Entity* GetIn() const { return m_In; }
    void SetOut(Entity* out) { m_Out = out; }
	const Entity* GetOut() const { return m_Out; }
	const Vector2f& GetInOffset() const { return m_InOffset; }
	const Vector2f& GetOutOffset() const { return m_OutOffset; }
    bool GetIsInsertableOutOnly() const { return m_IsInsertableOutOnly; }
    void SetIsInsertableOutOnly(bool isInsertableOutOnly) { m_IsInsertableOutOnly = isInsertableOutOnly; }

private:
    InserterType m_InserterType;
    Entity* m_In;
    Entity* m_Out;
    Vector2f m_InOffset;
    Vector2f m_OutOffset;
    bool m_IsInsertableOutOnly;
};

ironEND_NAMESPACE