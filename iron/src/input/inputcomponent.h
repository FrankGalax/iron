#pragma once

#include <iron.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

class InputComponent : public Component
{
public:

private:

#pragma region usercodeclass
public:
	InputComponent(const Window* window) : m_Window(window) {}

	const Window* GetWindow() const { return m_Window; }
	Entity* GetClickedEntity() const { return m_ClickedEntity; }
	void SetClickedEntity(Entity* clickedEntity) { m_ClickedEntity = clickedEntity; }
	bool GetIsLeftMouseButtonPressed() const { return m_IsLeftMouseButtonPressed; }
	void SetIsLeftMouseButtonPressed(bool isLeftMouseButtonPressed) { m_IsLeftMouseButtonPressed = isLeftMouseButtonPressed; }
	bool GetWasLeftMouseButtonPressed() const { return m_WasLeftMouseButtonPressed; }
	void SetWasLeftMouseButtonPressed(bool wasLeftMouseButtonPressed) { m_WasLeftMouseButtonPressed = wasLeftMouseButtonPressed; }

private:
	Entity* m_ClickedEntity = nullptr;
	bool m_IsLeftMouseButtonPressed = false;
	bool m_WasLeftMouseButtonPressed = false;
	const Window* m_Window = nullptr;
#pragma endregion
};

ironEND_NAMESPACE