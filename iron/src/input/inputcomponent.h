#pragma once

#include <iron.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

class InputComponent : public Component
{
public:
	InputComponent(const Window* window) : m_Window(window) {}

	const Window* GetWindow() const { return m_Window; }
	Entity* GetClickedEntity() const { return m_ClickedEntity; }
	void SetClickedEntity(Entity* clickedEntity) { m_ClickedEntity = clickedEntity; }
	bool GetIsLeftMouseButtonPressed() const { return m_IsLeftMouseButtonPressed; }
	void SetIsLeftMouseButtonPressed(bool isLeftMouseButtonPressed) { m_IsLeftMouseButtonPressed = isLeftMouseButtonPressed; }

private:
	Entity* m_ClickedEntity = nullptr;
	bool m_IsLeftMouseButtonPressed = false;
	const Window* m_Window = nullptr;
};
ironEND_NAMESPACE