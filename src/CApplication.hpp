#ifndef CAPPLICATION_HPP_
#define CAPPLICATION_HPP_

#include <memory>
#include <stack>
#include "StateEngine/CGame_State.hpp"
#include "ResourceManager/CResourceHolder.hpp"
#include "Tools/CDisplay.hpp"
#include "Tools/DEBUG.hpp"
#include "StateEngine/CIntro_State.hpp"
#include "StateEngine/CMenu_State.hpp"
#include "StateEngine/CPlaying_State.hpp"

class CApplication
{
public:

	explicit CApplication();
	virtual ~CApplication();

	void runMainLoop();

	void pushState(std::unique_ptr<State::CGame_State> state);
	void popState();

	void changeState(std::unique_ptr<State::CGame_State> state);

	//getter des etats
	std::unique_ptr<State::CIntro> getIntro_State(void);
	std::unique_ptr<State::CMenu> getMenu_State(void);
	std::unique_ptr<State::CPlaying> getPlaying_State(void);

private:
	std::stack<std::unique_ptr<State::CGame_State>> _states;

	sf::Clock m_clock;

	// les differents etats
	std::unique_ptr<State::CIntro> m_intro;
	std::unique_ptr<State::CMenu> m_menu;
	std::unique_ptr<State::CPlaying> m_playing;
};

#endif
