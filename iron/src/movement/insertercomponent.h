#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <math/vector.h>

#pragma region usercode
#include <movement/movementenum.h>
#pragma endregion

ironBEGIN_NAMESPACE

class JSON;
class Entity;

class InserterComponent : public Component
{
public:
    InserterComponent() {}
    InserterComponent(InserterType inserterType, const Vector2f& inOffset, const Vector2f& outOffset) : m_InserterType(inserterType), m_InOffset(inOffset), m_OutOffset(outOffset) {}

    InserterType GetInserterType() const { return m_InserterType; }
    const Entity* GetIn() const { return m_In; }
    void SetIn(Entity* in) { m_In = in; }
    const Entity* GetOut() const { return m_Out; }
    void SetOut(Entity* out) { m_Out = out; }
    const Vector2f& GetInOffset() const { return m_InOffset; }
    const Vector2f& GetOutOffset() const { return m_OutOffset; }
    bool GetIsInsertableOutOnly() const { return m_IsInsertableOutOnly; }
    void SetIsInsertableOutOnly(bool isInsertableOutOnly) { m_IsInsertableOutOnly = isInsertableOutOnly; }

    virtual void ToJSON(JSON* j) override;
    virtual void FromJSON(JSON* j) override;

private:
    InserterType m_InserterType = InserterType::None;
    Entity* m_In = nullptr;
    Entity* m_Out = nullptr;
    Vector2f m_InOffset;
    Vector2f m_OutOffset;
    bool m_IsInsertableOutOnly = false;

#pragma region usercodeclass
public:
    InserterComponent(InserterType inserterType) : InserterComponent(inserterType, Vector2f::Zero, Vector2f::Zero) {}
#pragma endregion
};

ironEND_NAMESPACE