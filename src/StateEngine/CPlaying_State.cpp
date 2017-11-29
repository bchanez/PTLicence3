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

		//for (int i = 0; i < NB_PNJ; ++i)
			//m_listPNJ.push_back(CPNJ());
	}

	/*virtual*/ CPlaying::~CPlaying()
	{
		LOG("CPlaying Destructor\n");
	}

	void State::CPlaying::input()
	{
		m_character.getInput().gestionInputs();
	}

	void CPlaying::update(float dt)
	{
		for (int i = 0; i < NB_PNJ; ++i)
			m_listPNJ[i].update(dt);

		m_character.update(dt);
	}

	void CPlaying::draw()
	{
		for (int i = 0; i < NB_PNJ; ++i)
			CDisplay::draw(m_listPNJ[i]);

		CDisplay::draw(m_character);
	}
}
