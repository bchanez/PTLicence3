#pragma once

#include <memory>
#include <stack>
#include "ResourceManager/CResourceHolder.hpp"
#include "Tools/CDisplay.hpp"
#include "Tools/DEBUG.hpp"
#include "StateEngine/CGame_State.hpp"
#include "StateEngine/CIntro_State.hpp"
#include "StateEngine/CMenu_State.hpp"
#include "StateEngine/CConfigure_State.hpp"
#include "StateEngine/CPlaying_State.hpp"
#include "StateEngine/CPause_State.hpp"

// Inclusion cyclique

// Forward declaration type
namespace State {
	class CIntro;
	class CMenu;
	class CConfigure;
	class CPlaying;
	class CPause;
}

enum class EState
{
	e_intro,
	e_menu,
	e_configure,
	e_playing,
	e_pause
};

class CApplication
{
public:

	explicit CApplication(void);
	virtual ~CApplication(void);

	void runMainLoop(void);

	void initIntroState(void);
	void initMenuState(void);
	void initConfigureState(void);
	void initPlayingStateNewGame(int nombre_pnj);
	void initPlayingState(void);
	void initPauseState(void);

	void changeState(EState state);

private:
	std::map <EState, std::unique_ptr<State::CGame_State>> m_state;
	EState m_currentScene;

	sf::Clock m_clock;
};
