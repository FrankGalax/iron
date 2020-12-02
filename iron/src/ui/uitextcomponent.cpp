#include <ui/uitextcomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void UITextComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE