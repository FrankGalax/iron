#pragma once

#include <iron.h>
#include <ecs/component.h>

#pragma region usercode
#include <ui/uienums.h>
#pragma endregion

ironBEGIN_NAMESPACE

class JSON;

class UIComponent : public Component
{
public:
    UIComponent() {}
    UIState GetUIState() const { return m_UIState; }
    void SetUIState(UIState uIState) { m_UIState = uIState; }

    virtual void ToJSON(JSON* j) override;
    virtual void FromJSON(JSON* j) override;
    virtual void FromJSONResolve(JSON* j) override;

private:
    UIState m_UIState = UIState::None;
};

ironEND_NAMESPACE