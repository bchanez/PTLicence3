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

		m_listEntities.clear(); //Au cas où si ce ce n'est pas détruit ou en cas d'erreurs
	}

	void CPlaying::init(void)
	{
		m_key.escape = false;

		if(!m_client->getIsConnected())
		{
			m_listEntities.clear();

			m_client->connection();
			sf::Packet packetInitGame = m_client->receiveInitgame();

			sf::Uint16 sizeData;
			packetInitGame >>  m_indexCharacter;
			packetInitGame >>  sizeData;
			for(unsigned int i = 0; i < sizeData; ++i)
			{
				struct DataInit dataInit;
				packetInitGame >> dataInit; //On met le paquet dans les donnes

				if((dataInit.cclass).compare("CActor") == 0)
				{
					m_listEntities.push_back(std::make_unique<CActor>(dataInit));
				}
				else if ((dataInit.cclass).compare("CEvent_pub") == 0)
				{
					m_listEntities.push_back(std::make_unique<CEvent_pub>(dataInit));
				}
			}

			dynamic_cast<CActor *>(m_listEntities[m_indexCharacter].get())->setIsCharacter(true); //Cast; Pour le PNJ à l'index du joueur, on dit que c'est un joueur
		}

		// centre la vue sur la position du personnage (Diviser par deux et zoomé)
		CDisplay::getView()->setSize(1920.f/2, 1080.f/2);
		CDisplay::getView()->setCenter(m_listEntities[m_indexCharacter].get()->getPosition());
		CDisplay::getWindow()->setView(* CDisplay::getView());

		m_client->sendState(3); //Synchro totale
	}

	void CPlaying::input(sf::Event * event)
	{
		m_data = m_listEntities[m_indexCharacter].get()->getData(); //On prend les données du perso qu'on dirige
		struct Data data = m_data;

		if((* event).type == sf::Event::KeyPressed)
		{
			if ((* event).key.code == sf::Keyboard::Z
			|| (* event).key.code == sf::Keyboard::W)
			data.keyUp = true;

			if ((* event).key.code == sf::Keyboard::Q
			|| (* event).key.code == sf::Keyboard::A)
			data.keyLeft = true;

			if ((* event).key.code == sf::Keyboard::S)
			data.keyDown = true;

			if ((* event).key.code == sf::Keyboard::D)
			data.keyRight = true;

			if ((* event).key.code == sf::Keyboard::LShift)
			data.keyShift = true;

			if((* event).key.code == sf::Keyboard::Escape)
			m_key.escape = true;
		}


		if((* event).type == sf::Event::KeyReleased)
		{
			if ((* event).key.code == sf::Keyboard::Z
			|| (* event).key.code == sf::Keyboard::W)
			data.keyUp = false;

			if ((* event).key.code == sf::Keyboard::Q
			|| (* event).key.code == sf::Keyboard::A)
			data.keyLeft = false;

			if ((* event).key.code == sf::Keyboard::S)
			data.keyDown = false;

			if ((* event).key.code == sf::Keyboard::D)
			data.keyRight = false;

			if ((* event).key.code == sf::Keyboard::LShift)
			data.keyShift = false;

			if ((* event).key.code == sf::Keyboard::Escape)
			m_key.escape = false;
		}

		if ((* event).type == sf::Event::MouseButtonPressed)
		{
			if ((* event).mouseButton.button == sf::Mouse::Left)
			data.mouseLeft = true;
		}

		if ((* event).type == sf::Event::MouseButtonReleased)
		{
			if((* event).mouseButton.button == sf::Mouse::Left)
			data.mouseLeft = false;
		}

		//envoie uniquement les touches si changements par rapport au ancienne data envoye
		if(m_data != data && m_listEntities[m_indexCharacter]->getData().state != 6 && m_listEntities[m_indexCharacter]->getData().state != 9)
		{
			sf::Packet p;
			m_data = data;
			m_listEntities.at(m_indexCharacter)->setData(m_data);
			m_data.mustUpdatePosition = true;
			p << m_data;
			m_client->addPacketToSend(p);
		}
	}

	void CPlaying::update(float dt)
	{
		//update de la scene
		if (m_key.escape)
		{
			m_application->initState(EState::e_pause);
			m_application->changeState(EState::e_pause);
			return;
		}

		// met a jour par rapport aux donnees recues
		std::vector<sf::Packet> listPacket = m_client->getListPacketReceive();
		for(unsigned int k = 0; k < listPacket.size(); ++k)
		{
			sf::Uint16 sizeData;
			listPacket[k] >> sizeData;
			for (unsigned int i = 0; i < sizeData; ++i)
			{
				struct Data data;
				listPacket[k] >> data;

				for (unsigned int j = 0; j < m_listEntities.size(); ++j)
				try {
					if(m_listEntities.at(j)->getData().index == data.index)
					{
						m_listEntities.at(j)->setData(data);
						break;
					}
				}
				catch (std::exception const& e){
					std::cout << "---------- Error Setting Client Datas : " << e.what() << std::endl;
				}
			}

			// update des entites
			int numberCActor = 0;
			for (unsigned int i = 0; i < m_listEntities.size(); ++i)
			{
				try {
					if (m_listEntities.at(i)->getDataInit().cclass == "CActor")
					{
						numberCActor++;

						if(dynamic_cast<CActor *>(m_listEntities[i].get())->getMustDisappear())
						{
							std::cout  << "delete \n";
							m_listEntities.erase(m_listEntities.begin() + i);

							//le perso est mort donc scene perdu
							if (m_indexCharacter == i)
							{
								std::cout << "perdu" << std::endl;
								m_client->sendState(4);
								m_client->disconnection();  //Déco du client
								m_application->setResult("lose");
								m_application->initState(EState::e_result);
								m_application->changeState(EState::e_result);
							}

							//On décale si le perso est après le mort
							if (m_indexCharacter > i)
								m_indexCharacter--;
						}

						// il ne reste que le joueur donc scene gagne
						if (numberCActor == 1 && i == m_listEntities.size() - 1)
						{
							std::cout << "gagner" << std::endl;
							m_client->disconnection();  //Déco du client
							m_application->setResult("win");
							m_application->initState(EState::e_result);
							m_application->changeState(EState::e_result);
						}
					}

					m_listEntities.at(i)->update(false, dt);
					if(m_listEntities.at(i).get()->getData().index == m_indexCharacter)
					{
						struct Data d = m_listEntities.at(i).get()->getData();
						std::cout <<
						d.index << " " <<
						d.state << " " <<
						d.mustUpdatePosition << " " <<
						d.positionX << " " << d.positionY << " " <<
						d.keyLeft << " " << d.keyRight << " " << d.keyUp << " " << d.keyDown << " " << d.keyShift << " " << d.mouseLeft <<
						std::endl;
					}

				}
				catch (std::exception const& e){
					std::cout << "---------- Error Update Client : " << e.what() << std::endl;
				}
			}
		}

		m_client->removePacketReceivedFromBeginingToIndex(listPacket.size());

		// update de la profondeur des Entity
		quickSort(m_listEntities, 0, (int)m_listEntities.size() - 1);
	}

	void CPlaying::draw()
	{
		// dessine la map
		CDisplay::draw(m_map);

		// dessines toutes les entites
		for (unsigned int i = 0; i < m_listEntities.size(); ++i)
		CDisplay::draw(*(m_listEntities[i].get()));
	}

	// trie rapide des entites par rapport a leurs positions sur l'axe y
	void CPlaying::quickSort(std::vector<std::unique_ptr<CEntity>>& tab, int begining, int ending)
	{
		int left = begining-1;
		int right = ending+1;
		const float pivot = tab[begining]->getPosition().y;

		if(begining >= ending)
		return;

		while(1)
		{
			do right--; while(tab[right]->getPosition().y > pivot);
			do left++; while(tab[left]->getPosition().y < pivot);

			if(left < right)
			{
				std::swap(tab[left], tab[right]);

				// change l'indice de la position du character dans le tab
				if (left == m_indexCharacter)
				m_indexCharacter = right;
				else if (right == m_indexCharacter)
				m_indexCharacter = left;
			}
			else break;
		}

		quickSort(tab, begining, right);
		quickSort(tab, right+1, ending);
	}
}
