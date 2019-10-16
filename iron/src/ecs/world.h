#pragma once

#include <iron.h>
#include <vector>

ironBEGIN_NAMESPACE

class Entity;
class System;
class Window;

class World
{
public:
	~World();

	void CreateSystems();
	Entity* CreateEntity();
	void RegisterEntity(Entity* entity);

	void Update(float deltaTime);
	void Render(Window* window);

private:
	std::vector<Entity*> m_Entities;
	std::vector<System*> m_UpdateSystems;
	std::vector<System*> m_RenderSystems;
	int m_NextEntityId = 0;
};

ironEND_NAMESPACE