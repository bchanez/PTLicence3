#include "CPlaying_State.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/DEBUG.hpp"
#include <iostream>

#define NB_PNJ 15

namespace State
{
	/*explicit*/ CPlaying::CPlaying(CApplication & application)
		: CGame_State(application)
	{
		LOG("CPlaying Constructor\n");

		//m_listPNJ.assign(NB_PNJ, CPNJ());
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
		//for (unsigned int i = 0; i < m_listPNJ.size(); ++i)
			//m_listPNJ[i].update(dt);

		m_character.update(dt);
	}

	void CPlaying::draw()
	{
		//for (unsigned int i = 0; i < m_listPNJ.size(); ++i)
			//CDisplay::draw(m_listPNJ[i]);

		CDisplay::draw(m_character);
	}
}
