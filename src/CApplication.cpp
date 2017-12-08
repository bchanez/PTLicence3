#include "CApplication.hpp"

/*explicit*/ CApplication::CApplication()
{
	LOG("CApplication Constructor\n");
	CDisplay::init();

	m_intro = std::make_unique<State::CIntro>(*this);
	m_menu = std::make_unique<State::CMenu>(*this);
	m_playing = std::make_unique<State::CPlaying>(*this);

	pushState(getIntro_State());
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

		_states.top()->input (& event);
		_states.top()->update (dt);
		_states.top()->draw ();

		CDisplay::display();
	}
}

void CApplication::pushState(std::unique_ptr<State::CGame_State> state)
{
	_states.push(std::move(state));
}

void CApplication::popState()
{
	_states.pop();
}

void CApplication::changeState(std::unique_ptr<State::CGame_State> state)
{
	_states.pop	();
	_states.push(std::move(state));
}

//getter des etats
std::unique_ptr<State::CIntro> CApplication::getIntro_State(void)
{
	return std::move(m_intro);
}

std::unique_ptr<State::CMenu> CApplication::getMenu_State(void)
{
	return std::move(m_menu);
}

std::unique_ptr<State::CPlaying> CApplication::getPlaying_State(void)
{
	return std::move(m_playing);
}
