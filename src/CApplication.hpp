#pragma once

#include <memory>
#include <stack>
#include "ResourceManager/CResourceHolder.hpp"
#include "Tools/CDisplay.hpp"
#include "Tools/DEBUG.hpp"
#include "StateEngine/CGame_State.hpp"
#include "StateEngine/CIntro_State.hpp"
#include "StateEngine/CMenu_State.hpp"
#include "StateEngine/CPlaying_State.hpp"
#include "StateEngine/CPause_State.hpp"
#include "StateEngine/CResult_State.hpp"
#include "Server/CClient.hpp"

// Inclusion cyclique

// Forward declaration type
namespace State {
	class CIntro;
	class CMenu;
	class CPlaying;
	class CPause;
	class CResult;
}

enum class EState
{
	e_intro,
	e_menu,
	e_playing,
	e_pause,
	e_result
};

class CApplication
{
public:

	explicit CApplication(void);	//Constructeur
	virtual ~CApplication(void);	//Destructeur

	void runMainLoop(void);				//Lance en boucle
	void initState(EState state);
	void changeState(EState state);

	void setResult(std::string str);

private:
	std::map <EState, std::unique_ptr<State::CGame_State>> m_state;
	EState m_currentScene;		//Scene courant (pause, menu, jeu, etc...)

	sf::Clock m_clock;

	CClient m_client;		//Quand on va init le côté client
};
