#include "CApplication.hpp"
#include "Tools/CDisplay.hpp"
#include "Tools/DEBUG.hpp"
#include "StateEngine/CPlaying_State.hpp"

/*explicit*/ CApplication::CApplication()
{
	LOG("CApplication Constructor\n");
	CDisplay::init();

	pushState(std::make_unique<State::CPlaying>(*this));
}

/*virtual*/ CApplication::~CApplication()
{
	LOG("CApplication Destructor\n");
}

void CApplication::runMainLoop()
{
	while (CDisplay::isOpen()) {
		float dt = m_clock.restart().asSeconds();

		CDisplay::checkWindowEvents();
		CDisplay::clear();

		_states.top()->input ();
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
