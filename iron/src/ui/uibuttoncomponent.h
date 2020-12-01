#pragma once

#include <iron.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

class UIButtonComponent : public Component
{
public:
    UIButtonComponent(ButtonType buttonType) : m_ButtonType(buttonType) {}

    ButtonType GetButtonType() const { return m_ButtonType; }

private:
    ButtonType m_ButtonType;
};

ironEND_NAMESPACE