#include <ui/uispritecomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void UISpriteComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE