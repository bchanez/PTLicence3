#ifndef CMENU_STATE_HPP_
#define CMENU_STATE_HPP_

#include "CGame_State.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/DEBUG.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace State
{
	class CMenu : public CGame_State
	{
		public:
			explicit CMenu(CApplication& application);
			virtual ~CMenu();

			void input() override;
			void update(float dt) override;
			void draw() override;

		private:
	};
}

#endif
