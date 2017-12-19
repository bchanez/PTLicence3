#pragma once

#include "CGame_State.hpp"
#include "../CApplication.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/CButton.hpp"
#include "../Tools/DEBUG.hpp"

namespace State
{
	class CConfigure : public CGame_State
	{
			struct Key { bool escape; };

		public:
			explicit CConfigure(CApplication& application);
			virtual ~CConfigure();

			void init(void);
			void input(sf::Event * event) override;
			void update(float dt) override;
			void draw() override;

		private:
			Key m_key;

			sf::Sprite m_configure;

			enum EButton {e_jouer, e_retour };
			std::vector<std::unique_ptr<CButton>> m_listButton;
	};
}
