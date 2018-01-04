#include "CApplication.hpp"

/*explicit*/ CApplication::CApplication(void)
{
	LOG("CApplication Constructor\n");
	CDisplay::init();

	m_state.insert(std::make_pair(EState::e_intro, std::make_unique<State::CIntro>(*this)));
	m_state.insert(std::make_pair(EState::e_menu, std::make_unique<State::CMenu>(*this)));
	m_state.insert(std::make_pair(EState::e_playing, std::make_unique<State::CPlaying>(*this)));
	m_state.insert(std::make_pair(EState::e_pause, std::make_unique<State::CPause>(*this)));

	m_currentScene = EState::e_intro;
	dynamic_cast<State::CIntro *>(m_state[m_currentScene].get())->init();
}

/*virtual*/ CApplication::~CApplication(void)
{
	LOG("CApplication Destructor\n");
}

void CApplication::runMainLoop(void)
{
	while (CDisplay::isOpen())
	{
		float dt = m_clock.restart().asSeconds();
		sf::Event event;

		CDisplay::clear();

		m_state[m_currentScene]->input(& event);
		m_state[m_currentScene]->update(dt);
		m_state[m_currentScene]->draw();

		CDisplay::display();
	}
}

void CApplication::initIntroState(void)
{
	dynamic_cast<State::CIntro *>(m_state[EState::e_intro].get())->init();
}

void CApplication::initMenuState(void)
{
	dynamic_cast<State::CMenu *>(m_state[EState::e_menu].get())->init();
}

void CApplication::initPlayingStateNewGame(int nombre_pnj)
{
	dynamic_cast<State::CPlaying *>(m_state[EState::e_playing].get())->newGame(nombre_pnj);
}

void CApplication::initPlayingState(void)
{
	dynamic_cast<State::CPlaying *>(m_state[EState::e_playing].get())->init();
}

void CApplication::initPauseState(void)
{
	dynamic_cast<State::CPause *>(m_state[EState::e_pause].get())->init();
}

void CApplication::changeState(EState state)
{
	m_currentScene = state;
}
