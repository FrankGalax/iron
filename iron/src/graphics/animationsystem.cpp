#include <graphics/animationsystem.h>
#include <graphics/animationcomponent.h>
#include <graphics/spritecomponent.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2(AnimationSystem, AnimationSystemTuple, AnimationComponent, SpriteComponent);

void AnimationSystem::Update(float deltaTime)
{
    for (AnimationSystemTuple& tuple : m_Tuples)
    {
        const float timer = tuple.m_AnimationComponent->GetTimer() - deltaTime;
        tuple.m_AnimationComponent->SetTimer(timer);

        if (timer <= 0)
        {
            const std::vector<AnimationSprite>& animationSprites = tuple.m_AnimationComponent->GetAnimationSprites();
            
            const int index = (tuple.m_AnimationComponent->GetAnimationSpriteIndex() + 1) % animationSprites.size();
            tuple.m_AnimationComponent->SetAnimationSpriteIndex(index);

            tuple.m_AnimationComponent->SetTimer(timer + tuple.m_AnimationComponent->GetTime());

            const AnimationSprite& animationSprite = animationSprites[index];
            const int x = animationSprite.m_SpriteSheetX;
            const int y = animationSprite.m_SpriteSheetY;
            tuple.m_SpriteComponent->SetSpriteSheetX(x);
            tuple.m_SpriteComponent->SetSpriteSheetY(y);

            sf::Sprite& sprite = tuple.m_SpriteComponent->GetSprite();
            if (sprite.getTexture() != nullptr)
            {
                sprite.setTextureRect(sf::IntRect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE));
            }
        }
    }
}

ironEND_NAMESPACE