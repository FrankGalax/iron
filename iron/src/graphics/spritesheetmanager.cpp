#include <graphics/spritesheetmanager.h>
#include <assert.h>

ironBEGIN_NAMESPACE

void SpriteSheetManager::LoadSpriteSheet()
{
    if (!m_SpriteSheet.loadFromFile("spritesheet.png"))
    {
        assert(false);
    }
}

ironEND_NAMESPACE