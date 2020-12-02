#pragma once

#include <iron.h>
#include <ecs/component.h>

#pragma region usercode
#include <ui/button.h>
#pragma endregion

ironBEGIN_NAMESPACE

class JSON;

class UIButtonComponent : public Component
{
public:
    UIButtonComponent(ButtonType buttonType) : m_ButtonType(buttonType) {}

    ButtonType GetButtonType() const { return m_ButtonType; }

    virtual void ToJSON(JSON* j) override;

private:
    ButtonType m_ButtonType;
};

ironEND_NAMESPACE