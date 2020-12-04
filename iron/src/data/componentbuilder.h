#pragma once

#include <iron.h>

ironBEGIN_NAMESPACE

class Component;

class ComponentBuilder
{
public:
    static Component* BuildComponent(int classHash);
};

ironEND_NAMESPACE