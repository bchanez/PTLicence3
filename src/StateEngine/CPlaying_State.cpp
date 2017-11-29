#include "CPlaying_State.hpp"

#define NB_PNJ 15

namespace State
{
	/*explicit*/ CPlaying::CPlaying(CApplication & application)
		: CGame_State(application)
	{
		LOG("CPlaying Constructor\n");

		for(int i = 0; i < NB_PNJ; i++)
			m_listPNJ.push_back(std::make_unique<CPNJ>());
		//m_listPNJ.assign(NB_PNJ, std::make_unique<CPNJ>);
	}

	/*virtual*/ CPlaying::~CPlaying()
	{
		m_listPNJ.clear();
		LOG("CPlaying Destructor\n");
	}

	void State::CPlaying::input()
	{
		m_character.getInput().gestionInputs();
	}

	void CPlaying::update(float dt)
	{
		for (unsigned int i = 0; i < m_listPNJ.size(); ++i)
			m_listPNJ[i].get()->update(dt);

		m_character.update(dt);
	}

	void CPlaying::draw()
	{
		for (unsigned int i = 0; i < m_listPNJ.size(); ++i)
			CDisplay::draw(*(m_listPNJ[i].get()));

		CDisplay::draw(m_character);
	}
}
