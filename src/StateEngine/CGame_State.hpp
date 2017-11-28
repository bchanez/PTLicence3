#ifndef GAME_STATE_HPP_
#define GAME_STATE_HPP_

#include "../ResourceManager/CResourceHolder.hpp"

class CApplication;

namespace State
{
	class CGame_State
	{
	public:
		explicit CGame_State(CApplication& application);
		virtual ~CGame_State();

		virtual void input() = 0;
		virtual void update(float dt)	= 0;
		virtual void draw()	= 0;

	protected:
		CApplication* _p_application;
	};
}

#endif
