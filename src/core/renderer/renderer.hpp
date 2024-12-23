#pragma once

#include "base.hpp"

namespace trimana::core {

	enum class rendering_api {
		opengl		= TRIMANA_BIT(0),
		vulkan		= TRIMANA_BIT(1),
		directx		= TRIMANA_BIT(2)
	};
}