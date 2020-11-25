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
        if (sprite.getTexture() == nullptr)
        {
            sprite.setTexture(tuple.m_Entity->GetWorld()->GetSpriteSheetManager().GetSpriteSheet());
            const int x = tuple.m_SpriteComponent->GetSpriteSheetX();
            const int y = tuple.m_SpriteComponent->GetSpriteSheetY();
            sprite.setTextureRect(sf::IntRect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE));
            if (!ironNullWithEpsilon(tuple.m_SpriteComponent->GetRotation()))
            {
                sprite.setOrigin(sf::Vector2f(GRID_SIZE / 2.f, GRID_SIZE / 2.f));
                sprite.setRotation(tuple.m_SpriteComponent->GetRotation());
            }

            sprite.setScale(tuple.m_SpriteComponent->GetScaleX() * RENDER_SCALE, tuple.m_SpriteComponent->GetScaleY() * RENDER_SCALE);
        }

        const Vector2f& position = tuple.m_PositionComponent->GetPosition();
        const sf::Vector2f origin = tuple.m_SpriteComponent->GetSprite().getOrigin();
        sprite.setPosition((position.GetX() * GRID_SIZE + origin.x) * RENDER_SCALE, (position.GetY() * GRID_SIZE + origin.y) * RENDER_SCALE);
        window->Draw(&sprite);
    }
}

void SpriteRenderSystem::OnRegisterEntity()
{
    std::sort(m_Tuples.begin(), m_Tuples.end(), [](const SpriteRenderSystemTuple& tuple1, const SpriteRenderSystemTuple& tuple2)
        {
            return tuple1.m_SpriteComponent->GetPriority() < tuple2.m_SpriteComponent->GetPriority();
        });
}

ironEND_NAMESPACE