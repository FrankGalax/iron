#pragma once

#include <iron.h>

ironBEGIN_NAMESPACE

struct SpriteInfo
{
	int m_SpriteSheetX = 0;
	int m_SpriteSheetY = 0;
	float m_ScaleX = 1.f;
	float m_ScaleY = 1.f;
	float m_Rotation = 0.f;
	int m_Priority = 0;
};

ironEND_NAMESPACE