#include <graphics/animationcomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void AnimationComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 757536853;
    for (AnimationSprite& animationSprite : m_AnimationSprites)
    {
        JSON subJSON;
        animationSprite.ToJSON(&subJSON);
        j["animationSprites"].push_back(subJSON.GetJ());
    }
    j["animationSpriteIndex"] = m_AnimationSpriteIndex;
    j["time"] = m_Time;
}

void AnimationComponent::FromJSON(JSON* json)
{
}

ironEND_NAMESPACE