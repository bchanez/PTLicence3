#include "CPlaying_State.hpp"

#define NB_PNJ 100

namespace State
{
	/*explicit*/ CPlaying::CPlaying(CApplication & application)
		: CGame_State(application)
	{
		LOG("CPlaying Constructor\n");

		// ajout du joueur
		m_indiceCharacter = 0;
		m_listEntite.push_back(std::make_unique<CCharacter>());

		// ajout des PNJs
		for(int i = 0; i < NB_PNJ; i++)
			m_listEntite.push_back(std::make_unique<CPNJ>());

		// ajout des evenement
	}

	/*virtual*/ CPlaying::~CPlaying()
	{
		m_listEntite.clear();
		LOG("CPlaying Destructor\n");
	}

	void State::CPlaying::input()
	{
		// met a jour les touches appuyees pour le personnage
		dynamic_cast<CCharacter *>(m_listEntite[m_indiceCharacter].get())->getInput().gestionInputs();
	}

	void CPlaying::update(float dt)
	{
		// update des entites
		for (unsigned int i = 0; i < m_listEntite.size(); ++i)
			m_listEntite[i]->update(dt);

		// update de la profondeur des Entity
		updateDepthOfEntity();
	}

	void CPlaying::draw()
	{
		// dessine la map
		CDisplay::draw(m_map);

		// dessines toutes les entites
		for (unsigned int i = 0; i < m_listEntite.size(); ++i)
			CDisplay::draw(*(m_listEntite[i].get()));
	}

	void CPlaying::updateDepthOfEntity(void)
	{
		// trie par ordre decroisant de la position sur l'axe y
		for(unsigned int i = 0; i < m_listEntite.size(); ++i)
				for(unsigned int j = i; j < m_listEntite.size(); ++j)
						if(m_listEntite[j]->getPosition().y < m_listEntite[i]->getPosition().y)
						{
								std::swap(m_listEntite[j], m_listEntite[i]);

								// change l'indice de la position du character dans le tableau
								if (i == m_indiceCharacter)
									m_indiceCharacter = j;
								else if (j == m_indiceCharacter)
									m_indiceCharacter = i;
						}
	}
}
