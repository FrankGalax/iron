#include <graphics/animationcomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void AnimationComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    for (AnimationSprite& animationSprite : m_AnimationSprites)
    {
        JSON subJSON;
        animationSprite.ToJSON(&subJSON);
        j["animationSprites"].push_back(subJSON.GetJ());
    }
    j["animationSpriteIndex"] = m_AnimationSpriteIndex;
    j["time"] = m_Time;
    j["timer"] = m_Timer;
}

ironEND_NAMESPACE