#include "CApplication.hpp"

/*explicit*/ CApplication::CApplication()
{
	LOG("CApplication Constructor\n");
	CDisplay::init();

	pushState(std::make_unique<State::CIntro>(*this));
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
