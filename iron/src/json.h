#pragma once

#include <iron.h>
#include <nlohmann/json.hpp>

ironBEGIN_NAMESPACE

class JSON
{
public:
	nlohmann::json& GetJ() { return m_J; }

private:
	nlohmann::json m_J;
};

ironEND_NAMESPACE