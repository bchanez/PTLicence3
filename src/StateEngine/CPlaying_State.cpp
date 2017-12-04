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

		m_listEntite.push_back(std::make_unique<CEvent_pub>());
		//m_listEntite[m_listEntite.size()-1].get()->setPosition(sf::Vector2f(300, 300));
	}

	/*virtual*/ CPlaying::~CPlaying()
	{
		m_listEntite.clear();
		LOG("CPlaying Destructor\n");
	}

	void CPlaying::input()
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
		quickSort(m_listEntite, 0, (int)m_listEntite.size() - 1);
	}

	void CPlaying::draw()
	{
		// dessine la map
		CDisplay::draw(m_map);

		// dessines toutes les entites
		for (unsigned int i = 0; i < m_listEntite.size(); ++i)
			CDisplay::draw(*(m_listEntite[i].get()));
	}

	void CPlaying::quickSort(std::vector<std::unique_ptr<CEntity>>& tableau, int debut, int fin)
	{
			int gauche = debut-1;
			int droite = fin+1;
			const float pivot = tableau[debut]->getPosition().y;

			if(debut >= fin)
					return;

			while(1)
			{
					do droite--; while(tableau[droite]->getPosition().y > pivot);
					do gauche++; while(tableau[gauche]->getPosition().y < pivot);

					if(gauche < droite)
					{
						std::swap(tableau[gauche], tableau[droite]);

						// change l'indice de la position du character dans le tableau
						if (gauche == m_indiceCharacter)
							m_indiceCharacter = droite;
						else if (droite == m_indiceCharacter)
							m_indiceCharacter = gauche;
					}
					else break;
			}

			quickSort(tableau, debut, droite);
			quickSort(tableau, droite+1, fin);
	}

}
