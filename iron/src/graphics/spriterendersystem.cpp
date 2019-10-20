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
			sprite.setTextureRect(sf::IntRect(x * SPRITESHEET_SIZE, y * SPRITESHEET_SIZE, SPRITESHEET_SIZE, SPRITESHEET_SIZE));
			sprite.setScale(2.f, 2.f);
		}

		sprite.setPosition(tuple.m_PositionComponent->GetX(), tuple.m_PositionComponent->GetY());
		window->Draw(&sprite);
	}
}

ironEND_NAMESPACE