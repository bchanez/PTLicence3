#include "CPlaying_State.hpp"

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
	  CDisplay::getView()->setCenter(m_listEntite[m_indiceCharacter].get()->getPosition());
	  CDisplay::getWindow()->setView(* CDisplay::getView());
	}

	void CPlaying::newGame(void)
	{
		m_key.escape = false;

		m_listEntite.clear();

		m_UDPserver.bind(55003);
		sf::Socket::Status status = m_TCPserver.connect("localhost", 55001);
		if (status != sf::Socket::Done)
		{
		    LOG("erreur connection \n");
		}

		sf::Packet packetInitGame;
		if (m_TCPserver.receive(packetInitGame) != sf::Socket::Done)
		{
			LOG("erreur reception client tcp\n");
		}
		else
		{
			LOG("reception client OK tcp\n");
		}
		m_TCPserver.disconnect();

		sf:: Uint16 tailleDonnee;
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
/*
		// ajout du joueur
		m_indiceCharacter = 0;
		m_listEntite.push_back(std::make_unique<CActor>(true));
		m_listEntite[m_indiceCharacter].get()->setPosition(sf::Vector2f(CRandom::floatInRange(100.f, 1820.f), CRandom::floatInRange(100.f, 980.f)));

		// ajout des PNJs
		int indiceDecalage = m_listEntite.size();
		for(int i = indiceDecalage; i < 100 + indiceDecalage; i++)
		{
			m_listEntite.push_back(std::make_unique<CActor>(false));
			m_listEntite[i].get()->setPosition(sf::Vector2f(CRandom::floatInRange(100.f, 1820.f), CRandom::floatInRange(100.f, 980.f)));
		}

		// ajout des evenement
		m_listEntite.push_back(std::make_unique<CEvent_pub>());
		m_listEntite[m_listEntite.size()-1].get()->setPosition(sf::Vector2f(300, 300));
*/

		// centre la vue sur la position du personnage
		CDisplay::getView()->setSize(1920.f/2, 1080.f/2);
		CDisplay::getView()->setCenter(m_listEntite[m_indiceCharacter].get()->getPosition());
		CDisplay::getWindow()->setView(* CDisplay::getView());
	}

	void CPlaying::input(sf::Event * event)
	{
		struct Donnees donnees = m_donneesSend;
		donnees.indice = m_indiceCharacter;

		while (CDisplay::getWindow()->pollEvent(* event))
    {
			// event de la scene
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

			if ((* event).type == sf::Event::MouseButtonPressed && (* event).mouseButton.button == sf::Mouse::Left)
			{
				m_listEntite[m_indiceCharacter]->setState(4); //e_attack
			}

		}

		//envoie les touches du client au serveur
		if(m_donneesSend != donnees)
		{
			sf::Packet packet;
			m_donneesSend = donnees;
			std::cout <<
			m_donneesSend.keyLeft << " " <<
			m_donneesSend.keyRight << " " <<
			m_donneesSend.keyUp << " " <<
			m_donneesSend.keyDown << " " <<
			m_donneesSend.keyShift << std::endl;
			packet << m_donneesSend;
			if(m_UDPserver.send(packet, "localhost", 55002)  == sf::Socket::Done)
			{
				std::cout << "envoei info client\n";
			}
			else
			{
				std::cout << "marche pas\n";
			}
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


		//recoie les donnees du serveur
		struct Donnees donnees;
		sf:: Uint16 tailleDonnee;
		sf::Packet packet;
		sf::IpAddress serveur;
		unsigned short port;
		if(m_UDPserver.receive(packet, serveur, port) == sf::Socket::Done)
		{
			//LOG("reception OK udp\n");
			packet >> tailleDonnee;
			for (unsigned int i = 0; i < tailleDonnee; ++i)
			{
				packet >> donnees;
				m_listEntite[donnees.indice]->setDonnees(donnees);
			}
		}

		/*
		char in[128];
		std::size_t received;
		sf::IpAddress sender;
		unsigned short senderPort;
		if (m_UDPserver.receive(in, sizeof(in), received, sender, senderPort) == sf::Socket::Done)
		{
			std::cout << "Message received from " << sender << ": \"" << senderPort << ": \"" << in << "\"" << std::endl;
		}
		else
		{
			std::cout << "error udp\n";
		}
		*/

		// update des entites
		for (unsigned int i = 0; i < m_listEntite.size(); ++i)
		{
			if (m_listEntite[i]->getState() == 4)
			{
				for (unsigned int j = 0; j < m_listEntite.size(); ++j)
				{
	        if (m_listEntite[i]->getPosition() != m_listEntite[j]->getPosition())
	        {
						if (m_listEntite[i]->getPosition().x > m_listEntite[j]->getPosition().x - 20
							&& m_listEntite[i]->getPosition().x < m_listEntite[j]->getPosition().x + 20
							&& m_listEntite[i]->getPosition().y > m_listEntite[j]->getPosition().y - 20
								&& m_listEntite[i]->getPosition().y < m_listEntite[j]->getPosition().y + 20)
	          m_listEntite[j]->setState(5);	//e_dead
	        }
				}
      }

			if (m_listEntite[i]->getState() == 8)	//e_disappear
			{
				m_listEntite.erase(m_listEntite.begin() + i);
				if (m_indiceCharacter > i)
					m_indiceCharacter--;
			}

			m_listEntite[i]->update(dt);
		}

		// update de la profondeur des Entity
		//quickSort(m_listEntite, 0, (int)m_listEntite.size() - 1);


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
