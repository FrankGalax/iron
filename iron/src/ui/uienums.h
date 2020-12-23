#pragma once

#include <iron.h>

ironBEGIN_NAMESPACE

enum class ButtonType
{
	None,
	X,
	Inventory,
	Move
};

enum class UIState
{
	None,
	Action,
	Inventory
};

ironEND_NAMESPACE