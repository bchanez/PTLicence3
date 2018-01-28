#include "CPlaying_State.hpp"

namespace State
{
	/*explicit*/ CPlaying::CPlaying(CApplication & application, CClient * client)
		: CGame_State(application)
	{
		LOG("CPlaying Constructor\n");

		m_client = client;
	}

	/*virtual*/ CPlaying::~CPlaying()
	{
		LOG("CPlaying Destructor\n");

		m_listEntite.clear(); //Au cas où si ce ce n'est pas détruit ou en cas d'erreurs
	}

	void CPlaying::init(void)
	{
		 m_key.escape = false;

		// centre la vue sur la position du personnage (Diviser par deux et zoomé)
		CDisplay::getView()->setSize(1920.f/2, 1080.f/2);
	  CDisplay::getView()->setCenter(m_listEntite[m_indiceCharacter].get()->getPosition());
	  CDisplay::getWindow()->setView(* CDisplay::getView());
	}

	void CPlaying::newGame(void)
	{
		m_key.escape = false;

		m_listEntite.clear();

		m_client->connexion();
		sf::Packet packetInitGame = m_client->receiveInitgame();

		sf::Uint16 tailleDonnee;
		packetInitGame >>  m_indiceCharacter;
		packetInitGame >>  tailleDonnee;
		for(unsigned int i = 0; i < tailleDonnee; ++i)
		{
			struct DonneesInit donneesInit;
			packetInitGame >> donneesInit; //On met le paquet dans les donnes

			if((donneesInit.classe).compare("CActor") == 0)
			{
				m_listEntite.push_back(std::make_unique<CActor>(donneesInit));
			}
			else if ((donneesInit.classe).compare("CEvent_pub") == 0)
			{
				m_listEntite.push_back(std::make_unique<CEvent_pub>(donneesInit));
			}
		}

		dynamic_cast<CActor *>(m_listEntite[m_indiceCharacter].get())->setIsCharacter(true); //Cast; Pour le PNJ à l'indice du joueur, on dit que c'est un joueur

		// centre la vue sur la position du personnage
		CDisplay::getView()->setSize(1920.f/2, 1080.f/2);
		CDisplay::getView()->setCenter(m_listEntite[m_indiceCharacter]->getPosition());
		CDisplay::getWindow()->setView(* CDisplay::getView());

		m_client->sendState(3); //Synchro totale pour le temps qu'il a mis a créer
	}

	void CPlaying::input(sf::Event * event)
	{
		m_donnees = m_listEntite[m_indiceCharacter].get()->getDonnees(); //On prend les données du perso qu'on dirige
		struct Donnees donnees = m_donnees;

    if((* event).type == sf::Event::KeyPressed)
		{
			if ((* event).key.code == sf::Keyboard::Z
				|| (* event).key.code == sf::Keyboard::W)
				donnees.keyUp = true;

			if ((* event).key.code == sf::Keyboard::Q
				|| (* event).key.code == sf::Keyboard::A)
				donnees.keyLeft = true;

			if ((* event).key.code == sf::Keyboard::S)
				donnees.keyDown = true;

			if ((* event).key.code == sf::Keyboard::D)
				donnees.keyRight = true;

			if ((* event).key.code == sf::Keyboard::LShift)
				donnees.keyShift = true;

			if((* event).key.code == sf::Keyboard::Escape)
				m_key.escape = true;
		}


		if((* event).type == sf::Event::KeyReleased)
		{
			if ((* event).key.code == sf::Keyboard::Z
				|| (* event).key.code == sf::Keyboard::W)
				donnees.keyUp = false;

			if ((* event).key.code == sf::Keyboard::Q
				|| (* event).key.code == sf::Keyboard::A)
				donnees.keyLeft = false;

			if ((* event).key.code == sf::Keyboard::S)
				donnees.keyDown = false;

			if ((* event).key.code == sf::Keyboard::D)
				donnees.keyRight = false;

			if ((* event).key.code == sf::Keyboard::LShift)
				donnees.keyShift = false;

			if ((* event).key.code == sf::Keyboard::Escape)
				m_key.escape = false;
		}

		if ((* event).type == sf::Event::MouseButtonPressed)
		{
			if ((* event).mouseButton.button == sf::Mouse::Left)
				donnees.mouseLeft = true;
		}

		if ((* event).type == sf::Event::MouseButtonReleased)
		{
			if((* event).mouseButton.button == sf::Mouse::Left)
				donnees.mouseLeft = false;
		}

		//envoie uniquement les touches si changements par rapport au ancienne donnees envoye
		if(m_donnees != donnees)
		{
			sf::Packet p;
			m_donnees = donnees;
			p << m_donnees;
			m_client->addPacketToSend(p);
		}
	}

	void CPlaying::update(float dt)
	{
		//update de la scene
		if (m_key.escape)
		{
			m_client->sendState(1); //On ne fait rien (pas de réception de données)
			m_application->initPauseState();
			m_application->changeState(EState::e_pause);
			return;
		}

		// met a jour par rapport aux donnees recues
		std::vector<sf::Packet> listePacket = m_client->getListPacketReceive();
		for(unsigned int k = 0; k < listePacket.size(); ++k)
		{
			sf::Uint16 tailleDonnee;
			listePacket[k] >> tailleDonnee;
			for (unsigned int i = 0; i < tailleDonnee; ++i)
			{
				struct Donnees donnees;
				listePacket[k] >> donnees;

				for (unsigned int j = 0; j < m_listEntite.size(); ++j)
					if(m_listEntite[j]->getDonnees().indice == donnees.indice)
					{
						m_listEntite[j]->setDonnees(donnees);
						break;
					}
			}

			// update des entites
			for (unsigned int i = 0; i < m_listEntite.size(); ++i)
			{
				if (m_listEntite[i]->getDonneesInit().classe == "CActor" && dynamic_cast<CActor *>(m_listEntite[i].get())->getMustDisappear())
				{
					std::cout  << "delete \n";
					m_listEntite.erase(m_listEntite.begin() + i);
					if (m_indiceCharacter > i) //On décale si le perso est après le mort
						m_indiceCharacter--;
				}

				m_listEntite[i]->update(false, dt);
			}
		}

		m_client->removePacketReceivedFromBeginingToIndice(listePacket.size());

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
