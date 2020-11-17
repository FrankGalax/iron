#include <graphics/uisystem.h>
#include <data/entitybuilder.h>
#include <ecs/world.h>
#include <graphics/spriteinfo.h>
#include <graphics/uicomponent.h>
#include <graphics/window.h>
#include <input/clickedcomponent.h>
#include <input/inputcomponent.h>
#include <item/inventorycomponent.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_OR_3(UISystem, UISystemTuple, UIComponent, ClickedComponent, InputComponent);

void DrawSprite(sf::Sprite& sprite, Window* window, float x, float y)
{
	sprite.setPosition(x * GRID_SIZE * RENDER_SCALE, y * GRID_SIZE * RENDER_SCALE);
	window->Draw(&sprite);
};

void DrawText(sf::Text& text, Window* window, float x, float y)
{
	text.setPosition(x * GRID_SIZE * RENDER_SCALE, y * GRID_SIZE * RENDER_SCALE);
	window->Draw(&text);
};

void UISystem::Update(float deltaTime)
{
	UIComponent* uiComponent = nullptr;
	ClickedComponent* clickedComponent = nullptr;
	InputComponent* inputComponent = nullptr;

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
		if (tuple.m_InputComponent != nullptr)
		{
			inputComponent = tuple.m_InputComponent;
		}
	}

	if (clickedComponent == nullptr || inputComponent == nullptr || uiComponent->GetButtons().empty())
	{
		return;
	}

	if (!inputComponent->GetIsLeftMouseButtonPressed() || inputComponent->GetWasLeftMouseButtonPressed())
	{
		return;
	}

	const sf::RenderWindow& window = inputComponent->GetWindow()->GetSFMLWindow();
	sf::Vector2i sfPosition = sf::Mouse::getPosition(window);
	if (sfPosition.x >= 0 && sfPosition.x < (int)window.getSize().x && sfPosition.y >= 0 && sfPosition.y < (int)window.getSize().y)
	{
		for (const Button& button : uiComponent->GetButtons())
		{
			const sf::Sprite& sprite = button.m_Sprite;
			const sf::Vector2f& spritePosition = sprite.getPosition();
			if (sfPosition.x >= spritePosition.x && sfPosition.x < spritePosition.x + (GRID_SIZE * RENDER_SCALE) &&
				sfPosition.y >= spritePosition.y && sfPosition.y < spritePosition.y + (GRID_SIZE * RENDER_SCALE))
			{
				switch (button.m_ButtonType)
				{
				case ButtonType::X:
				{
					World* world = clickedComponent->GetOwner()->GetWorld();
					world->RemoveComponent(clickedComponent);
					world->ResetEntity(clickedComponent->GetOwner());
					inputComponent->SetClickedEntity(nullptr);
				}
				break;
				}
			}
		}
	}
}

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

	if (clickedComponent != nullptr)
	{
		InventoryComponent* inventoryComponent = clickedComponent->GetOwner()->GetComponent<InventoryComponent>(); 
		if (inventoryComponent != nullptr)
		{
			if (uiComponent->GetBorderTopLeft().getTexture() == nullptr)
			{
				InitBaseSprites(uiComponent);
			}

			if (inventoryComponent->GetIsDirtyForUI())
			{
				inventoryComponent->SetIsDirtyForUI(false);
				InitInventorySprites(uiComponent, inventoryComponent);
			}

			const int sizeX = 10;
			const int sizeY = 3;
			const float screenSizeX = window->GetSFMLWindow().getSize().x / (float)(GRID_SIZE * RENDER_SCALE);
			const float screenSizeY = window->GetSFMLWindow().getSize().y / (float)(GRID_SIZE * RENDER_SCALE);
			const int fullSizeX = sizeX + 2;
			const int fullSizeY = sizeY + 2;
			const float topLeftX = screenSizeX / 2.f - fullSizeX / 2.f;
			const float topLeftY = screenSizeY / 2.f - fullSizeY / 2.f;

			DrawInventoryUI(uiComponent, inventoryComponent, window, topLeftX, topLeftY, sizeX, sizeY);
		}
	}
	else
	{
		constexpr InventoryComponent* inventoryComponent = nullptr;
		InitInventorySprites(uiComponent, inventoryComponent);
	}
}

void UISystem::InitBaseSprites(UIComponent* uiComponent)
{
	const sf::Texture& spriteSheet = uiComponent->GetOwner()->GetWorld()->GetSpriteSheetManager().GetSpriteSheet();

	const auto initSprite = [&spriteSheet](sf::Sprite& sprite, int x, int y, float rotation, float scaleX, float scaleY)
	{
		sprite.setTexture(spriteSheet);
		sprite.setTextureRect(sf::IntRect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE));
		sprite.setScale(scaleX * RENDER_SCALE, scaleY * RENDER_SCALE);
		sprite.setRotation(rotation);
	};

	initSprite(uiComponent->GetTitleTopLeft(), 24, 10, 0.f, 1.f, 1.f);
	initSprite(uiComponent->GetTitleBackground(), 24, 11, 0.f, 1.f, 1.f);
	initSprite(uiComponent->GetTitleTopRight(), 24, 10, 0.f, -1.f, 1.f);
	initSprite(uiComponent->GetBorderTopLeft(), 24, 6, 0.f, 1.f, 1.f);
	initSprite(uiComponent->GetBorderTop(), 24, 8, 0.f, 1.f, 1.f);
	initSprite(uiComponent->GetBorderLeft(), 24, 7, 0.f, 1.f, 1.f);
	initSprite(uiComponent->GetBorderBottomLeft(), 24, 6, 270.f, 1.f, 1.f);
	initSprite(uiComponent->GetBorderBottom(), 24, 8, 180.f, 1.f, 1.f);
	initSprite(uiComponent->GetBorderBottomRight(), 24, 6, 180.f, 1.f, 1.f);
	initSprite(uiComponent->GetBorderRight(), 24, 7, 180.f, 1.f, 1.f);
	initSprite(uiComponent->GetBorderTopRight(), 24, 6, 90.f, 1.f, 1.f);
	initSprite(uiComponent->GetInventoryBackground(), 24, 9, 0.f, 1.f, 1.f);

	sf::Font& font = uiComponent->GetFont();
	bool success = font.loadFromFile("arial.ttf");
	assert(success);
	sf::Text& quantityText = uiComponent->GetQuantityText();
	quantityText.setFont(font);
	quantityText.setFillColor(sf::Color::White);
	quantityText.setCharacterSize(14);

	sf::Text& titleText = uiComponent->GetTitleText();
	titleText.setFont(font);
	titleText.setFillColor(sf::Color::Black);
	titleText.setCharacterSize(20);

	Button xButton;
	initSprite(xButton.m_Sprite, 24, 12, 0.f, 1.f, 1.f);
	xButton.m_ButtonType = ButtonType::X;
	uiComponent->GetButtons().push_back(xButton);
}

void UISystem::InitInventorySprites(UIComponent* uiComponent, const InventoryComponent* inventoryComponent)
{
	for (sf::Sprite* sprite : uiComponent->GetInventorySprites())
	{
		delete sprite;
	}
	uiComponent->GetInventorySprites().clear();

	if (inventoryComponent == nullptr)
	{
		return;
	}

	const sf::Texture& spriteSheet = uiComponent->GetOwner()->GetWorld()->GetSpriteSheetManager().GetSpriteSheet();

	for (const InventoryItem& item : inventoryComponent->GetItems())
	{
		sf::Sprite* sprite = new sf::Sprite();
		SpriteInfo spriteInfo;
		EntityBuilder::BuildSpriteInfoFromResource(spriteInfo, item.m_ResourceType);

		sprite->setTexture(spriteSheet);
		sprite->setTextureRect(sf::IntRect(spriteInfo.m_SpriteSheetX * GRID_SIZE, spriteInfo.m_SpriteSheetY * GRID_SIZE, GRID_SIZE, GRID_SIZE));
		sprite->setScale(spriteInfo.m_ScaleX * RENDER_SCALE, spriteInfo.m_ScaleY * RENDER_SCALE);
		uiComponent->GetInventorySprites().push_back(sprite);
	}
}

void UISystem::DrawInventoryUI(UIComponent* uiComponent, const InventoryComponent* inventoryComponent, Window* window, float topLeftX, 
	float topLeftY, int sizeX, int sizeY)
{
	DrawSprite(uiComponent->GetTitleTopLeft(), window, topLeftX, topLeftY);
	DrawSprite(uiComponent->GetTitleTopRight(), window, topLeftX + sizeX + 2.f, topLeftY);

	for (float i = 0; i < sizeX; i += 1.f)
	{
		DrawSprite(uiComponent->GetTitleBackground(), window, topLeftX + i + 1.f, topLeftY);
		DrawSprite(uiComponent->GetBorderTop(), window, topLeftX + i + 1.f, topLeftY);
		DrawSprite(uiComponent->GetBorderBottom(), window, topLeftX + i + 2.f, topLeftY + sizeY + 2.f);
	}

	DrawSprite(uiComponent->GetButtons()[0].m_Sprite, window, topLeftX + sizeX, topLeftY);

	uiComponent->GetTitleText().setString(inventoryComponent->GetOwner()->GetName());
	DrawText(uiComponent->GetTitleText(), window, topLeftX + 1.f, topLeftY + 0.1f);

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

	const std::vector<InventoryItem>& items = inventoryComponent->GetItems();
	for (int i = 0; i < uiComponent->GetInventorySprites().size(); ++i)
	{
		const int row = i / sizeX;
		const int column = i % sizeX;
		DrawSprite(*uiComponent->GetInventorySprites()[i], window, topLeftX + column + 1.f, topLeftY + row + 1.f);
		
		uiComponent->GetQuantityText().setString(std::to_string(items[i].m_Quantity));
		DrawText(uiComponent->GetQuantityText(), window, topLeftX + column + 1.7f, topLeftY + row + 1.45f);
	}
}

ironEND_NAMESPACE