#include <ui/uirendersystem.h>
#include <ecs/world.h>
#include <ui/uispritecomponent.h>
#include <graphics/window.h>
#include <movement/positioncomponent.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2(UIRenderSystem, UIRenderSystemTuple, UISpriteComponent, PositionComponent)

void UIRenderSystem::Render(Window* window)
{
    for (UIRenderSystemTuple& tuple : m_Tuples)
    {
        sf::Sprite& sprite = tuple.m_UISpriteComponent->GetSprite();
        if (sprite.getTexture() == nullptr)
        {
            sprite.setTexture(tuple.m_Entity->GetWorld()->GetSpriteSheetManager().GetSpriteSheet());
            const int x = tuple.m_UISpriteComponent->GetSpriteSheetX();
            const int y = tuple.m_UISpriteComponent->GetSpriteSheetY();
            sprite.setTextureRect(sf::IntRect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE));
            if (!ironNullWithEpsilon(tuple.m_UISpriteComponent->GetRotation()))
            {
                sprite.setOrigin(sf::Vector2f(GRID_SIZE / 2.f, GRID_SIZE / 2.f));
                sprite.setRotation(tuple.m_UISpriteComponent->GetRotation());
            }

            sprite.setScale(tuple.m_UISpriteComponent->GetScaleX() * RENDER_SCALE, tuple.m_UISpriteComponent->GetScaleY() * RENDER_SCALE);
        }

        const Vector2f& position = tuple.m_PositionComponent->GetPosition();
        const sf::Vector2f origin = tuple.m_UISpriteComponent->GetSprite().getOrigin();
        sprite.setPosition((position.GetX() * GRID_SIZE + origin.x) * RENDER_SCALE, (position.GetY() * GRID_SIZE + origin.y) * RENDER_SCALE);
        window->Draw(&sprite);
    }
}

void UIRenderSystem::OnRegisterEntity()
{
    std::sort(m_Tuples.begin(), m_Tuples.end(), [](const UIRenderSystemTuple& tuple1, const UIRenderSystemTuple& tuple2)
        {
            return tuple1.m_UISpriteComponent->GetPriority() < tuple2.m_UISpriteComponent->GetPriority();
        });
}

ironEND_NAMESPACE