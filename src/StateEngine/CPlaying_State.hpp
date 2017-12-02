#ifndef CPLAYING_STATE_HPP_
#define CPLAYING_STATE_HPP_

#include "CGame_State.hpp"
#include "../Entity/CMap.hpp"
#include "../Entity/CPNJ.hpp"
#include "../Entity/CCharacter.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/DEBUG.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace State
{
	class CPlaying : public CGame_State
	{
		public:
			explicit CPlaying(CApplication& application);
			virtual ~CPlaying();

			void input() override;
			void update(float dt) override;
			void draw() override;

		private:

			void updateDepthOfEntity(void);


			CMap m_map;

			std::vector<std::unique_ptr<CEntity>> m_listEntite; // joueur, pnj, evenement
			unsigned int m_indiceCharacter; // variable qui stoque l'indice du character dans le tableau
	};
}

#endif
