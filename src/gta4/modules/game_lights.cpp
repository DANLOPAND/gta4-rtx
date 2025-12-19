#include "std_include.hpp"
#include "game_lights.hpp"

namespace gta4
{
	game_lights::game_lights()
	{
		p_this = this;

		// -----
		m_initialized = true;
		shared::common::log("GameLights", "Module initialized.", shared::common::LOG_TYPE::LOG_TYPE_DEFAULT, false);
	}
}
