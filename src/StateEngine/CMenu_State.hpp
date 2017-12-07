#ifndef CMENU_STATE_HPP_
#define CMENU_STATE_HPP_

#include <memory>
#include <vector>
#include "CGame_State.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/DEBUG.hpp"
#include "CPlaying_State.hpp"

namespace State
{
	class CMenu : public CGame_State
	{
		public:
			explicit CMenu(CApplication& application);
			virtual ~CMenu();

			void input(sf::Event * event) override;
			void update(float dt) override;
			void draw() override;

		private:
			sf::Sprite m_menu;
	};
}

#endif
