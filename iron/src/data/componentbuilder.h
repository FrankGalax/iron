#pragma once

#include <iron.h>

ironBEGIN_NAMESPACE

class Component;
class Entity;

class ComponentBuilder
{
public:
    static Component* BuildComponent(int classHash);
    static Component* GetComponent(Entity* entity, int classHash);
};

ironEND_NAMESPACE