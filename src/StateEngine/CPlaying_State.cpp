#include "CPlaying_State.hpp"

namespace State
{
	/*explicit*/ CPlaying::CPlaying(CApplication & application)
		: CGame_State(application)
	{
		LOG("CPlaying Constructor\n");

		m_UDPserver.setBlocking(false);

		//m_serveur = "192.168.43.26";
		m_serveur = "localhost";
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
	  CDisplay::getView()->setCenter(m_listEntite[m_indiceCharacter].get()->getPosition());
	  CDisplay::getWindow()->setView(* CDisplay::getView());
	}

	void CPlaying::newGame(void)
	{
		m_key.escape = false;

		m_listEntite.clear();

		m_UDPserver.bind(55003);
		sf::Socket::Status status = m_TCPserver.connect(m_serveur, 55001);
		if (status != sf::Socket::Done)
		{
		    LOG("erreur connection \n");
				exit(0);
		}

		sf::Packet packetInitGame;
		if (m_TCPserver.receive(packetInitGame) != sf::Socket::Done)
		{
			LOG("erreur reception tcp\n");
		}
		else
		{
			LOG("reception tcp ok\n");
		}
		m_TCPserver.disconnect();

		sf::Uint16 tailleDonnee;
		struct DonneesInit donneesInit;

		packetInitGame >>  m_indiceCharacter;
		packetInitGame >>  tailleDonnee;
		for(unsigned int i = 0; i < tailleDonnee; ++i)
		{
			packetInitGame >> donneesInit;

			if((donneesInit.classe).compare("CActor") == 0)
			{
				m_listEntite.push_back(std::make_unique<CActor>(donneesInit));
			}
			else if ((donneesInit.classe).compare("CEvent_pub") == 0)
			{
				m_listEntite.push_back(std::make_unique<CEvent_pub>(donneesInit));
			}
		}

		dynamic_cast<CActor *>(m_listEntite[m_indiceCharacter].get())->setIsCharacter(true);

		// centre la vue sur la position du personnage
		CDisplay::getView()->setSize(1920.f/2, 1080.f/2);
		CDisplay::getView()->setCenter(m_listEntite[m_indiceCharacter]->getPosition());
		CDisplay::getWindow()->setView(* CDisplay::getView());
	}

	void CPlaying::input(sf::Event * event)
	{
		m_donnees = m_listEntite[m_indiceCharacter].get()->getDonnees();
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
			m_donnees = donnees;
			send();
		}
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

		receive();
		
		// update des entites
		for (unsigned int i = 0; i < m_listEntite.size(); ++i)
		{
			if (m_listEntite[i]->getDonneesInit().classe == "CActor" && dynamic_cast<CActor *>(m_listEntite[i].get())->getMustDisappear())
			{
				m_listEntite.erase(m_listEntite.begin() + i);
				if (m_indiceCharacter > i)
					m_indiceCharacter--;
			}

			m_listEntite[i]->update(false, dt);
		}

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

	void CPlaying::receive(void)
	{
			sf:: Uint16 tailleDonnee;
			struct Donnees donnees; donnees.indice = 0;
			sf::Packet packet;
			sf::IpAddress serveur;
			unsigned short port;
			if(m_UDPserver.receive(packet, serveur, port) == sf::Socket::Done)
			{
				packet >> tailleDonnee;
				for (unsigned int i = 0; i < tailleDonnee; ++i)
				{
					packet >> donnees;

					for (unsigned int j = 0; j < m_listEntite.size(); ++j)
						if(m_listEntite[j]->getDonnees().indice == donnees.indice)
						{
							m_listEntite[j]->setDonnees(donnees);
							break;
						}
				}
			}
	}

	void CPlaying::send(void)
	{
			sf::Packet packet;
			packet << m_donnees;
			m_UDPserver.send(packet, m_serveur, 55002);
	}
}
