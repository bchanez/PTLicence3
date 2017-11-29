#ifndef PLAYING_STATE_HPP_
#define PLAYING_STATE_HPP_

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
		CMap m_map;
		std::vector<std::unique_ptr<CPNJ>> m_listPNJ;
		CCharacter m_character;
	};
}

#endif
