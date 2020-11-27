#pragma once

#include <iron.h>

ironBEGIN_NAMESPACE

class Entity;

class Component
{
public:
    virtual ~Component() {}

    Entity* GetOwner() { return m_Owner; }
    const Entity* GetOwner() const { return m_Owner; }
    void SetOwner(Entity* owner) { m_Owner = owner; }

private:
    Entity* m_Owner = nullptr;
};

ironEND_NAMESPACE