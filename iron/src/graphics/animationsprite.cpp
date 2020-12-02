#include <graphics/animationsprite.h>
#include <json.h>

ironBEGIN_NAMESPACE

void AnimationSprite::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["spriteSheetX"] = m_SpriteSheetX;
    j["spriteSheetY"] = m_SpriteSheetY;
}

ironEND_NAMESPACE