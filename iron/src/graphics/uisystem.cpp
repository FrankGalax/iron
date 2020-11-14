#include <graphics/uisystem.h>
#include <ecs/world.h>
#include <graphics/uicomponent.h>
#include <graphics/window.h>
#include <input/clickedcomponent.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_OR_2(UISystem, UISystemTuple, UIComponent, ClickedComponent);

void UISystem::Render(Window* window)
{
	UIComponent* uiComponent = nullptr;
	ClickedComponent* clickedComponent = nullptr;

	for (UISystemTuple& tuple : m_Tuples)
	{
		if (tuple.m_UIComponent != nullptr)
		{
			uiComponent = tuple.m_UIComponent;
		}
		if (tuple.m_ClickedComponent != nullptr)
		{
			clickedComponent = tuple.m_ClickedComponent;
		}
	}

	assert(uiComponent != nullptr);

	if (uiComponent != nullptr && uiComponent->GetBorderTopLeft().getTexture() == nullptr)
	{
		InitUIComponent(uiComponent);
	}

	if (clickedComponent != nullptr)
	{
		const auto drawSprite = [window](sf::Sprite& sprite, float x, float y)
		{
			sprite.setPosition(x * GRID_SIZE * RENDER_SCALE, y * GRID_SIZE * RENDER_SCALE);
			window->Draw(&sprite);
		};

		drawSprite(uiComponent->GetBorderTop(), 1.f, 0.f);
		drawSprite(uiComponent->GetBorderTop(), 2.f, 0.f);
		drawSprite(uiComponent->GetBorderTopLeft(), 0.f, 0.f);
		drawSprite(uiComponent->GetBorderLeft(), 0.f, 1.f);
		drawSprite(uiComponent->GetBorderLeft(), 0.f, 2.f);
		drawSprite(uiComponent->GetBorderBottomLeft(), 0.f, 4.f);
		drawSprite(uiComponent->GetBorderBottom(), 2.f, 4.f);
		drawSprite(uiComponent->GetBorderBottom(), 3.f, 4.f);
		drawSprite(uiComponent->GetBorderBottomRight(), 4.f, 4.f);
		drawSprite(uiComponent->GetBorderRight(), 4.f, 3.f);
		drawSprite(uiComponent->GetBorderRight(), 4.f, 2.f);
		drawSprite(uiComponent->GetBorderTopRight(), 4.f, 0.f);
	}
}

void UISystem::InitUIComponent(UIComponent* uiComponent)
{
	const sf::Texture& spriteSheet = uiComponent->GetOwner()->GetWorld()->GetSpriteSheetManager().GetSpriteSheet();

	const auto initSprite = [&spriteSheet](sf::Sprite& sprite, int x, int y, float rotation)
	{
		sprite.setTexture(spriteSheet);
		sprite.setTextureRect(sf::IntRect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE));
		sprite.setScale(RENDER_SCALE, RENDER_SCALE);
		sprite.setRotation(rotation);
	};

	initSprite(uiComponent->GetBorderTopLeft(), 24, 6, 0.f);
	initSprite(uiComponent->GetBorderTop(), 24, 8, 0.f);
	initSprite(uiComponent->GetBorderLeft(), 24, 7, 0.f);
	initSprite(uiComponent->GetBorderBottomLeft(), 24, 6, 270.f);
	initSprite(uiComponent->GetBorderBottom(), 24, 8, 180.f);
	initSprite(uiComponent->GetBorderBottomRight(), 24, 6, 180.f);
	initSprite(uiComponent->GetBorderRight(), 24, 7, 180.f);
	initSprite(uiComponent->GetBorderTopRight(), 24, 6, 90.f);
}

ironEND_NAMESPACE