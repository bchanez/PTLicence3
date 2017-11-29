#ifndef CAPPLICATION_HPP_
#define CAPPLICATION_HPP_

#include <memory>
#include <stack>
#include "StateEngine/CGame_State.hpp"
#include "ResourceManager/CResourceHolder.hpp"
#include "Tools/CDisplay.hpp"
#include "Tools/DEBUG.hpp"
#include "StateEngine/CPlaying_State.hpp"

class CApplication
{
public:
	explicit CApplication();
	virtual ~CApplication();

	void runMainLoop();

	void pushState	(std::unique_ptr<State::CGame_State> state);
	void popState	();

	void changeState(std::unique_ptr<State::CGame_State> state);

private:
	std::stack<std::unique_ptr<State::CGame_State>> _states;

	sf::Clock m_clock;
};

#endif
