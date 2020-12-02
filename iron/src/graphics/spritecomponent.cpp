#include <graphics/spritecomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void SpriteComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE