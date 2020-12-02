#pragma once

#include <iron.h>

#pragma region usercode
// test 1
#pragma endregion

ironBEGIN_NAMESPACE

class JSON;
class Entity;

#pragma region usercodenamespace
// test 2
#pragma endregion

class Component
{
public:
    virtual ~Component() {}

    Entity* GetOwner() { return m_Owner; }
    const Entity* GetOwner() const { return m_Owner; }
    void SetOwner(Entity* owner) { m_Owner = owner; }

    void ToJSON(JSON* j);

private:
    Entity* m_Owner = nullptr;

#pragma region usercodeclass
// test 3
#pragma endregion
};

ironEND_NAMESPACE