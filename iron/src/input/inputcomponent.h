#pragma once

#include <iron.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

class JSON;
class Entity;
class Window;

class InputComponent : public Component
{
public:
    InputComponent() {}
    InputComponent(const Window* window) : m_Window(window) {}

    Entity* GetClickedEntity() { return m_ClickedEntity; }
    const Entity* GetClickedEntity() const { return m_ClickedEntity; }
    void SetClickedEntity(Entity* clickedEntity) { m_ClickedEntity = clickedEntity; }
    bool GetIsLeftMouseButtonPressed() const { return m_IsLeftMouseButtonPressed; }
    void SetIsLeftMouseButtonPressed(bool isLeftMouseButtonPressed) { m_IsLeftMouseButtonPressed = isLeftMouseButtonPressed; }
    bool GetWasLeftMouseButtonPressed() const { return m_WasLeftMouseButtonPressed; }
    void SetWasLeftMouseButtonPressed(bool wasLeftMouseButtonPressed) { m_WasLeftMouseButtonPressed = wasLeftMouseButtonPressed; }
    bool GetIsSPressed() const { return m_IsSPressed; }
    void SetIsSPressed(bool isSPressed) { m_IsSPressed = isSPressed; }
    bool GetIsLPressed() const { return m_IsLPressed; }
    void SetIsLPressed(bool isLPressed) { m_IsLPressed = isLPressed; }
    const Window* GetWindow() const { return m_Window; }
    void SetWindow(const Window* window) { m_Window = window; }

    virtual void ToJSON(JSON* j) override;
    virtual void FromJSON(JSON* j) override;
    virtual void FromJSONResolve(JSON* j) override;

private:
    Entity* m_ClickedEntity = nullptr;
    bool m_IsLeftMouseButtonPressed = false;
    bool m_WasLeftMouseButtonPressed = false;
    bool m_IsSPressed = false;
    bool m_IsLPressed = false;
    const Window* m_Window = nullptr;
};

ironEND_NAMESPACE