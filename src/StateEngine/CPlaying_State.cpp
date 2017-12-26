#include "CPlaying_State.hpp"
#include "iostream"

namespace State
{
	/*explicit*/ CPlaying::CPlaying(CApplication & application)
		: CGame_State(application)
	{
		LOG("CPlaying Constructor\n");
	}

	/*virtual*/ CPlaying::~CPlaying()
	{
		LOG("CPlaying Destructor\n");

		m_listEntite.clear();
	}

	void CPlaying::init(void)
	{
		m_key.escape = false;

		// centre la vue sur la position du personnage
		CDisplay::getView()->setSize(1920.f/2, 1080.f/2);
	  CDisplay::getView()->setCenter(dynamic_cast<CCharacter *>(m_listEntite[m_indiceCharacter].get())->getPosition());
	  CDisplay::getWindow()->setView(* CDisplay::getView());
	}

	void CPlaying::newGame(int nombre_pnj)
	{
		m_key.escape = false;

		m_listEntite.clear();

		// ajout du joueur
		m_indiceCharacter = 0;
		m_listEntite.push_back(std::make_unique<CCharacter>());
		m_listEntite[m_indiceCharacter].get()->setPosition(sf::Vector2f((float)(rand()%1000), (float)(rand()%1000)));

		// ajout des PNJs
		int indiceDecalage = m_listEntite.size();
		for(int i = indiceDecalage; i < nombre_pnj + indiceDecalage; i++)
		{
			m_listEntite.push_back(std::make_unique<CPNJ>());
			m_listEntite[i].get()->setPosition(sf::Vector2f(CRandom::floatInRange(100.f, 1820.f), CRandom::floatInRange(100.f, 980.f)));
		}

		// ajout des evenement
		m_listEntite.push_back(std::make_unique<CEvent_pub>());
		m_listEntite[m_listEntite.size()-1].get()->setPosition(sf::Vector2f(300, 300));

		// centre la vue sur la position du personnage
		CDisplay::getView()->setSize(1920.f/2, 1080.f/2);
		CDisplay::getView()->setCenter(dynamic_cast<CCharacter *>(m_listEntite[m_indiceCharacter].get())->getPosition());
		CDisplay::getWindow()->setView(* CDisplay::getView());
	}

	void CPlaying::input(sf::Event * event)
	{
		// event de la scene
    if((* event).type == sf::Event::KeyPressed)
      if((* event).key.code == sf::Keyboard::Escape)
				m_key.escape = true;

		if((* event).type == sf::Event::KeyReleased)
			if ((* event).key.code == sf::Keyboard::Escape)
				m_key.escape = false;

		// met a jour les events pour le personnage
		dynamic_cast<CCharacter *>(m_listEntite[m_indiceCharacter].get())->input(&(* event));
	}

	void CPlaying::update(float dt)
	{
		//update de la scene
		if (m_key.escape)
		{
			m_application->initPauseState();
			m_application->changeState(EState::e_pause);
			return;
		}

		// update des entites
		for (unsigned int i = 0; i < m_listEntite.size(); ++i)
			m_listEntite[i]->update(dt);

		// update de la profondeur des Entity
		quickSort(m_listEntite, 0, (int)m_listEntite.size() - 1);
	}

	void CPlaying::draw()
	{
		// dessine la map
		CDisplay::draw(m_map);

		// dessines toutes les entites
		for (unsigned int i = 0; i < m_listEntite.size(); ++i)
			CDisplay::draw(*(m_listEntite[i].get()));
	}

	// trie rapide des entites par rapport a leurs positions sur l'axe y
	void CPlaying::quickSort(std::vector<std::unique_ptr<CEntity>>& tableau, int debut, int fin)
	{
			int gauche = debut-1;
			int droite = fin+1;
			const float pivot = tableau[debut]->getPosition().y;

			if(debut >= fin)
					return;

			while(1)
			{
					do droite--; while(tableau[droite]->getPosition().y > pivot);
					do gauche++; while(tableau[gauche]->getPosition().y < pivot);

					if(gauche < droite)
					{
						std::swap(tableau[gauche], tableau[droite]);

						// change l'indice de la position du character dans le tableau
						if (gauche == m_indiceCharacter)
							m_indiceCharacter = droite;
						else if (droite == m_indiceCharacter)
							m_indiceCharacter = gauche;
					}
					else break;
			}

			quickSort(tableau, debut, droite);
			quickSort(tableau, droite+1, fin);
	}

}
