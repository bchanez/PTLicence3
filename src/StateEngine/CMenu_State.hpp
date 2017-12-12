#pragma once

#include "CGame_State.hpp"
#include "../CApplication.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/DEBUG.hpp"


namespace State
{
	class CMenu : public CGame_State
	{
			struct Button { bool escape, space; };

		public:
			explicit CMenu(CApplication& application);
			virtual ~CMenu();

			void init(void);
			void input(sf::Event * event) override;
			void update(float dt) override;
			void draw() override;

		private:
			Button m_button;

			sf::Sprite m_menu;
	};
}
