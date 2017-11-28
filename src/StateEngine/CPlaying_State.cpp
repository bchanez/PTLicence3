#include "CPlaying_State.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/DEBUG.hpp"
#include <iostream>

namespace State
{
	/*explicit*/ CPlaying::CPlaying(CApplication & application)
		: CGame_State(application)
	{
		LOG("CPlaying Constructor\n");
	}

	/*virtual*/ CPlaying::~CPlaying()
	{
		LOG("CPlaying Destructor\n");
	}

	void State::CPlaying::input()
	{
		character.getInput().gestionInputs();
	}

	void CPlaying::update(float dt)
	{
		character.update(dt);
	}

	void CPlaying::draw()
	{
		CDisplay::draw(character);
	}
}
