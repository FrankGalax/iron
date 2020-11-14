#include <graphics/uisystem.h>
#include <ecs/world.h>
#include <graphics/uicomponent.h>
#include <graphics/window.h>
#include <input/clickedcomponent.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_OR_2(UISystem, UISystemTuple, UIComponent, ClickedComponent);

void DrawSprite(sf::Sprite& sprite, Window* window, float x, float y)
{
	sprite.setPosition(x * GRID_SIZE * RENDER_SCALE, y * GRID_SIZE * RENDER_SCALE);
	window->Draw(&sprite);
};

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
		const int sizeX = 10;
		const int sizeY = 3;
		const float screenSizeX = window->GetSFMLWindow().getSize().x / (float)(GRID_SIZE * RENDER_SCALE);
		const float screenSizeY = window->GetSFMLWindow().getSize().y / (float)(GRID_SIZE * RENDER_SCALE);
		const int fullSizeX = sizeX + 2;
		const int fullSizeY = sizeY + 2;
		const float topLeftX = screenSizeX / 2.f - fullSizeX / 2.f;
		const float topLeftY = screenSizeY / 2.f - fullSizeY / 2.f;

		DrawInventoryUI(uiComponent, window, topLeftX, topLeftY, sizeX, sizeY);
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
	initSprite(uiComponent->GetInventoryBackground(), 24, 9, 0.f);
}

void UISystem::DrawInventoryUI(UIComponent* uiComponent, Window* window, float topLeftX, float topLeftY, int sizeX, int sizeY)
{
	for (float i = 0; i < sizeX; i += 1.f)
	{
		DrawSprite(uiComponent->GetBorderTop(), window, topLeftX + i + 1.f, topLeftY);
		DrawSprite(uiComponent->GetBorderBottom(), window, topLeftX + i + 2.f, topLeftY + sizeY + 2.f);
	}

	for (float i = 0; i < sizeY; i += 1.f)
	{
		DrawSprite(uiComponent->GetBorderLeft(), window, topLeftX, topLeftY + i + 1.f);
		DrawSprite(uiComponent->GetBorderRight(), window, topLeftX + sizeX + 2.f, topLeftY + i + 2.f);
	}

	DrawSprite(uiComponent->GetBorderTopLeft(), window, topLeftX, topLeftY);
	DrawSprite(uiComponent->GetBorderBottomLeft(), window, topLeftX, topLeftY + sizeY + 2.f);
	DrawSprite(uiComponent->GetBorderBottomRight(), window, topLeftX + sizeX + 2.f, topLeftY + sizeY + 2.f);
	DrawSprite(uiComponent->GetBorderTopRight(), window, topLeftX + sizeX + 2.f, topLeftY);

	for (int i = 0; i < sizeX; ++i)
	{
		for (int j = 0; j < sizeY; ++j)
		{
			DrawSprite(uiComponent->GetInventoryBackground(), window, topLeftX + i + 1.f, topLeftY + j + 1.f);
		}
	}
}

ironEND_NAMESPACE