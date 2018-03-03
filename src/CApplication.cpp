#include "CApplication.hpp"

/*explicit*/ CApplication::CApplication(void)
{
	LOG("CApplication Constructor\n");
	CDisplay::init();	//Création fenêtre

	//Insertion tout les états possible (intro, menu, en jeu, pause, resultat)
	m_state.insert(std::make_pair(EState::e_intro, std::make_unique<State::CIntro>(*this)));
	m_state.insert(std::make_pair(EState::e_menu, std::make_unique<State::CMenu>(*this)));
	m_state.insert(std::make_pair(EState::e_playing, std::make_unique<State::CPlaying>(*this, &m_client)));
	m_state.insert(std::make_pair(EState::e_pause, std::make_unique<State::CPause>(*this, &m_client)));
	m_state.insert(std::make_pair(EState::e_result, std::make_unique<State::CResult>(*this)));

	m_currentScene = EState::e_intro;	//Premier état = intro
	m_state[m_currentScene]->init();	//Init intro
}

/*virtual*/ CApplication::~CApplication(void)
{
	LOG("CApplication Destructor\n");

	m_client.getThreadSend()->terminate();		//Termine les threads
	m_client.getThreadReceive()->terminate();
}

void CApplication::runMainLoop(void)
{
	// lance les thread poru recevoir et envoyer les donnees
	m_client.getThreadSend()->launch();
	m_client.getThreadReceive()->launch();

	while (CDisplay::isOpen())	//Fenâtre ouverte
	{
		float dt = m_clock.restart().asSeconds();
		sf::Event event;

		CDisplay::clear();

		while (CDisplay::getWindow()->pollEvent(event)) 		//En fonction de la scène, on l'affiche
			m_state[m_currentScene]->input(& event);
		m_state[m_currentScene]->update(dt);
		m_state[m_currentScene]->draw();

		CDisplay::display();		//On affiche
	}
}

void CApplication::initState(EState state)
{
	m_state[state]->init();
}

void CApplication::changeState(EState state)
{
	m_currentScene = state;
}

void CApplication::setResult(std::string str)
{
	dynamic_cast<State::CResult *>(m_state[EState::e_result].get())->setResult(str);
}
