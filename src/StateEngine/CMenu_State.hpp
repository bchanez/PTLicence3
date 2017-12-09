#ifndef CMENU_STATE_HPP_
#define CMENU_STATE_HPP_

#include "CGame_State.hpp"
#include "../CApplication.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/DEBUG.hpp"


namespace State
{
	class CIntro;
	class CPlaying;
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
