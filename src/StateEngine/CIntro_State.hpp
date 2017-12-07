#ifndef CINTRO_STATE_HPP_
#define CINTRO_STATE_HPP_

#include <memory>
#include <vector>
#include "CGame_State.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/DEBUG.hpp"
#include "CMenu_State.hpp"

namespace State
{
	class CIntro : public CGame_State
	{
		public:
			explicit CIntro(CApplication& application);
			virtual ~CIntro();

			void input(sf::Event * event) override;
			void update(float dt) override;
			void draw() override;

		private:
			sf::Sprite m_intro;
	};
}

#endif
