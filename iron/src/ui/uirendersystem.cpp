#include <ui/uirendersystem.h>
#include <ecs/world.h>
#include <ui/uispritecomponent.h>
#include <graphics/window.h>
#include <movement/positioncomponent.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2(UIRenderSystem, UIRenderSystemTuple, UISpriteComponent, PositionComponent)

void UIRenderSystem::Render(Window* window)
{
    std::sort(m_Tuples.begin(), m_Tuples.end(), [](const UIRenderSystemTuple& tuple1, const UIRenderSystemTuple& tuple2)
        {
            return tuple1.m_UISpriteComponent->GetPriority() < tuple2.m_UISpriteComponent->GetPriority();
        });

    for (UIRenderSystemTuple& tuple : m_Tuples)
    {
        sf::Sprite& sprite = tuple.m_UISpriteComponent->GetSprite();
        if (sprite.getTexture() == nullptr)
        {
            sprite.setTexture(tuple.m_Entity->GetWorld()->GetSpriteSheetManager().GetSpriteSheet());
            const int x = tuple.m_UISpriteComponent->GetSpriteSheetX();
            const int y = tuple.m_UISpriteComponent->GetSpriteSheetY();
            sprite.setTextureRect(sf::IntRect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE));
            sprite.setScale(tuple.m_UISpriteComponent->GetScaleX() * RENDER_SCALE, tuple.m_UISpriteComponent->GetScaleY() * RENDER_SCALE);
        }

        const Vector2f& position = tuple.m_PositionComponent->GetPosition();
        sprite.setPosition(position.GetX() * GRID_SIZE * RENDER_SCALE, position.GetY() * GRID_SIZE * RENDER_SCALE);
        window->Draw(&sprite);
    }
}

ironEND_NAMESPACE