#ifndef PLAYING_STATE_HPP_
#define PLAYING_STATE_HPP_

#include "CGame_State.hpp"
#include "../Tools/CAnimation.hpp"
#include "../Tools/CInput.hpp"
#include "../Entity/CCharacter.hpp"

namespace State
{
	class CPlaying : public CGame_State
	{
	public:
		CPlaying(CApplication& application);
		~CPlaying();

		void input() override;
		void update(float dt) override;
		void draw() override;

	private:
		CInput m_input;
		CCharacter character;
	};
}

#endif
