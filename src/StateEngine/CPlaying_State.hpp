#pragma once

#include <memory>
#include <vector>
#include "CGame_State.hpp"
#include <SFML/Network.hpp>
#include "../CApplication.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Entity/CMap.hpp"
#include "../Entity/CActor.hpp"
#include "../Entity/CEvent_pub.hpp"
#include "../Server/CClient.hpp"
#include "../Server/CData.hpp"
#include <exception>

namespace State
{
	class CPlaying : public CGame_State
	{
			struct Key { bool escape; };

		public:
			explicit CPlaying(CApplication& application, CClient * client);
			virtual ~CPlaying();

			void init(void) override;
			void input(sf::Event * event) override;
			void update(float dt) override;
			void draw() override;

		private:

			// client pour connecter avec le serveur
			CClient * m_client;

			struct Data m_data; //Pour les données du client
			void receive(void); //Nani?!

			Key m_key;

			void quickSort(std::vector<std::unique_ptr<CEntity>>& tableau, int debut, int fin); //Pour gérer la profondeur


			CMap m_map;

			std::vector<std::unique_ptr<CEntity>> m_listEntities; // joueur, pnj, evenement

			sf:: Uint16 m_indexCharacter; // variable qui stocke l'indice du character dans le tableau
	};
}
