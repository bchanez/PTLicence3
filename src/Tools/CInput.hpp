#pragma once

#include <SFML/Graphics.hpp>
#include "CDrawable.hpp"
#include "CAnimation.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "CCollision.hpp"
#include "DEBUG.hpp"

class CInput : public CDrawable
{
  struct Mouse { bool clicked; sf::Vector2f position; };

  public:
    explicit CInput(const sf::Texture * texture, sf::Vector2f position, sf::Vector2f taille);
    virtual ~CInput(void);

    void setTexture(const sf::Texture * texture);
    void setAnimation(void);

    void inputMousePosition(sf::Vector2f position);
    void inputMouseclicked(bool clicked);
    bool action(void);

    void init(void);
    void update(float dt);

  private:
    enum Estate {e_normal, e_hovered, e_cliked};
    unsigned int m_state;

		bool m_action;

    std::vector<CAnimation> m_animation;
    unsigned int m_nb_animation = 3;

    sf::Vector2f m_position;
    sf::Vector2f m_taille;
    
    sf::Text m_text;
    sf::Vector2f m_positionText;

    Mouse mouse;


    //Fonction pour afficher le rectangle
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_text, states);
    }
};
