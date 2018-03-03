#pragma once

#include "CGame_State.hpp"
#include "../CApplication.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/CButton.hpp"
#include "../Tools/DEBUG.hpp"

namespace State
{
	class CResult : public CGame_State
	{
			struct Key { bool escape; };

		public:
			explicit CResult(CApplication& application);
			virtual ~CResult();

			void init(void) override;
			void input(sf::Event * event) override;
			void update(float dt) override;
			void draw() override;

      void setResult(std::string str);

		private:
			Key m_key;

			sf::Sprite m_result;

			enum EButton {e_retour};
			std::vector<std::unique_ptr<CButton>> m_listButton;
	};
}
