#ifndef CINTRO_STATE_HPP_
#define CINTRO_STATE_HPP_

#include "CGame_State.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/DEBUG.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace State
{
	class CIntro : public CGame_State
	{
		public:
			explicit CIntro(CApplication& application);
			virtual ~CIntro();

			void input() override;
			void update(float dt) override;
			void draw() override;

		private:
	};
}

#endif
