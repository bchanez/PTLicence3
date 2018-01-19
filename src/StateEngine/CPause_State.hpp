#pragma once

#include "CGame_State.hpp"
#include "../CApplication.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/CButton.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Server/CClient.hpp"

namespace State
{
	class CPause : public CGame_State
	{
			struct Key { bool escape; };

		public:
			explicit CPause(CApplication& application, CClient * client);
			virtual ~CPause();

			void init(void);
			void input(sf::Event * event) override;
			void update(float dt) override;
			void draw() override;

		private:
			// client pour connecter avec le serveur
			CClient * m_client;
			
			Key m_key;

			sf::Sprite m_pause;

			enum EButton {e_retour, e_quitter};
			std::vector<std::unique_ptr<CButton>> m_listButton;
	};
}
