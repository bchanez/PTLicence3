#ifndef CAPPLICATION_HPP_
#define CAPPLICATION_HPP_

#include <memory>
#include <stack>
#include "StateEngine/CGame_State.hpp"
#include "ResourceManager/CResourceHolder.hpp"

class CApplication
{
public:
	CApplication();
	~CApplication();

	void runMainLoop();

	void pushState	(std::unique_ptr<State::CGame_State> state);
	void popState	();

	void changeState(std::unique_ptr<State::CGame_State> state);

private:
	std::stack<std::unique_ptr<State::CGame_State>> _states;
};

#endif
