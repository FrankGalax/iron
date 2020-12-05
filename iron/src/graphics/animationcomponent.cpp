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
    nlohmann::json& j = json->GetJ();
    for (nlohmann::json& animationSpriteJ : j["animationSprites"])
    {
        AnimationSprite animationSprite;
        JSON animationSpriteJSON(animationSpriteJ);
        animationSprite.FromJSON(&animationSpriteJSON);
        m_AnimationSprites.push_back(animationSprite);
    }
    m_AnimationSpriteIndex = j["animationSpriteIndex"];
    m_Time = j["time"];
}

void AnimationComponent::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    for (int i = 0; i < m_AnimationSprites.size(); ++i)
    {
        JSON animationSpriteJSON(j["animationSprites"][i]);
        m_AnimationSprites[i].FromJSONResolve(&animationSpriteJSON);
    }
}

ironEND_NAMESPACE