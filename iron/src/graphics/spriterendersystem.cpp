#include <graphics/spriterendersystem.h>
#include <ecs/world.h>
#include <graphics/spritecomponent.h>
#include <graphics/window.h>
#include <movement/positioncomponent.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2(SpriteRenderSystem, SpriteRenderSystemTuple, SpriteComponent, PositionComponent)

void SpriteRenderSystem::Render(Window* window)
{
    for (SpriteRenderSystemTuple& tuple : m_Tuples)
    {
        sf::Sprite& sprite = tuple.m_SpriteComponent->GetSprite();
        constexpr float scale = 2.f;
        if (sprite.getTexture() == nullptr)
        {
            sprite.setTexture(tuple.m_Entity->GetWorld()->GetSpriteSheetManager().GetSpriteSheet());
            const int x = tuple.m_SpriteComponent->GetSpriteSheetX();
            const int y = tuple.m_SpriteComponent->GetSpriteSheetY();
            sprite.setTextureRect(sf::IntRect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE));
            sprite.setScale(tuple.m_SpriteComponent->GetScaleX() * scale, tuple.m_SpriteComponent->GetScaleY() * scale);
        }

        const Vector2f& position = tuple.m_PositionComponent->GetPosition();
        sprite.setPosition(position.GetX() * GRID_SIZE * scale, position.GetY() * GRID_SIZE * scale);
        window->Draw(&sprite);
    }
}

ironEND_NAMESPACE