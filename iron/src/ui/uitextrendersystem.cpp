#include <ui/uitextrendersystem.h>
#include <ecs/world.h>
#include <ui/uitextcomponent.h>
#include <graphics/window.h>
#include <movement/positioncomponent.h>
#include <assert.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2(UITextRenderSystem, UITextRenderSystemTuple, UITextComponent, PositionComponent)

void UITextRenderSystem::Render(Window* window)
{
    for (UITextRenderSystemTuple& tuple : m_Tuples)
    {
        sf::Text& text = tuple.m_UITextComponent->GetText();
        if (text.getFont() == nullptr)
        {
            sf::Font& font = tuple.m_UITextComponent->GetFont();
            bool success = font.loadFromFile("arial.ttf");
            assert(success);
            text.setFont(font);
            text.setString(tuple.m_UITextComponent->GetString());
            text.setFillColor(tuple.m_UITextComponent->GetColor());
            text.setCharacterSize(tuple.m_UITextComponent->GetSize());
        }

        const Vector2f& position = tuple.m_PositionComponent->GetPosition();
        text.setPosition(position.GetX() * GRID_SIZE * RENDER_SCALE, position.GetY() * GRID_SIZE * RENDER_SCALE);
        window->Draw(&text);
    }
}

ironEND_NAMESPACE