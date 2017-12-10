#include "CApplication.hpp"

/*explicit*/ CApplication::CApplication()
{
	LOG("CApplication Constructor\n");
	CDisplay::init();

	m_state.insert(std::make_pair(EState::e_intro, std::make_unique<State::CIntro>(*this)));
	m_state.insert(std::make_pair(EState::e_menu, std::make_unique<State::CMenu>(*this)));
	m_state.insert(std::make_pair(EState::e_playing, std::make_unique<State::CPlaying>(*this)));

	m_currentScene = EState::e_intro;
}

/*virtual*/ CApplication::~CApplication()
{
	LOG("CApplication Destructor\n");
}

void CApplication::runMainLoop()
{
	while (CDisplay::isOpen()) {
		float dt = m_clock.restart().asSeconds();
		sf::Event event;

		CDisplay::clear();

		m_state[m_currentScene]->input(& event);
		m_state[m_currentScene]->update(dt);
		m_state[m_currentScene]->draw();

		CDisplay::display();
	}
}

void CApplication::changeState(EState state)
{
	m_currentScene = state;
}
