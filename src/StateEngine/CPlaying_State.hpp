#pragma once

#include <memory>
#include <vector>
#include "CGame_State.hpp"
#include "../CApplication.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Entity/CMap.hpp"
#include "../Entity/CPNJ.hpp"
#include "../Entity/CCharacter.hpp"
#include "../Entity/CEvent_pub.hpp"

namespace State
{
	class CPlaying : public CGame_State
	{
			struct Key { bool escape; };

		public:
			explicit CPlaying(CApplication& application);
			virtual ~CPlaying();

			void init(void);
			void newGame(int nombre_pnj);

			void input(sf::Event * event) override;
			void update(float dt) override;
			void draw() override;

		private:
			Key m_key;

			void quickSort(std::vector<std::unique_ptr<CEntity>>& tableau, int debut, int fin);

			CMap m_map;

			std::vector<std::unique_ptr<CEntity>> m_listEntite; // joueur, pnj, evenement
			int m_indiceCharacter; // variable qui stocke l'indice du character dans le tableau
	};
}
