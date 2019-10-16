#include <graphics/sfmlcirclerendersystem.h>
#include <graphics/window.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2(SFMLCircleRenderSystem, SFMLCircleRenderSystemTuple, SFMLCircleComponent, PositionComponent)

void SFMLCircleRenderSystem::Render(Window* window)
{
	for (SFMLCircleRenderSystemTuple& tuple : m_Tuples)
	{
		float x = tuple.m_PositionComponent->GetX();
		float y = tuple.m_PositionComponent->GetY();
		tuple.m_SFMLCircleComponent->GetCircleShape().setPosition(x, y);
		window->Draw(&tuple.m_SFMLCircleComponent->GetCircleShape());
	}
}

ironEND_NAMESPACE