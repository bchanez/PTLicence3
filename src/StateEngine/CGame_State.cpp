#include "CGame_State.hpp"
#include "../CApplication.hpp"
#include "../Tools/DEBUG.hpp"

namespace State {
	/*explicit*/ State::CGame_State::CGame_State(CApplication & application)
		: _p_application(&application)
	{
			LOG("CGame_State Constructor\n");
	}

	/*virtual*/ State::CGame_State::~CGame_State()
	{
		LOG("CGame_State Destructor\n");
	}
}
