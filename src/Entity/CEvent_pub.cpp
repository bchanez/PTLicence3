#include "CEvent_pub.hpp"

/*explicit*/ CEvent_pub::CEvent_pub(unsigned int indice)
{
  LOG("CEvent_pub Constructor\n");

  m_donneesInit.classe = "CEvent_pub";
  m_donneesInit.indice = indice;
  m_donnees.indice = indice;

  m_sprite.setOrigin(sf::Vector2f(100, 100));

  m_donnees.state = e_idle;

  setTexture();
  setAnimation();
}

/*explicit*/ CEvent_pub::CEvent_pub(struct DonneesInit donnees)
{
  LOG("CEvent_pub Constructor\n");

  m_donneesInit.indice = donnees.indice;
  m_donnees.indice = donnees.indice;

  m_sprite.setOrigin(sf::Vector2f(100, 100));

  m_donnees.state = e_idle;

  setPosition(sf::Vector2f(donnees.positionX, donnees.positionY));
  setTexture();
  setAnimation();
}

/*virtual*/ CEvent_pub::~CEvent_pub(void)
{
  LOG("CEvent_pub Destructor\n");
}

// donne la texture a l'evenemnt
void CEvent_pub::setTexture(void)
{
  m_sprite.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Pub));
}

// definie les animations de l'evenement
void CEvent_pub::setAnimation(void)
{
  for (unsigned int i = 0; i < m_nb_animation ; ++i)
    m_animation.push_back(CAnimation());

  for (int i = 0; i < 36 ; ++i)
  {
    m_animation[e_idle].addFrame(sf::IntRect(i * 200, 0, 200, 160), 0.1f);
    m_animation[e_call].addFrame(sf::IntRect(i * 200, 160, 200, 160), 0.1f);
    m_animation[e_active].addFrame(sf::IntRect(i * 200, 320, 200, 160), 0.1f);
  }
}

void CEvent_pub::input(void)
{

}

void CEvent_pub::update(bool isServer, float dt)
{
  (void)dt;
  (void)isServer;
  switch (m_donnees.state)
  {
    case e_idle :
    {
      m_sprite.setTextureRect(m_animation[e_idle].getFrame());
    }
    break;

    case e_call :
    {
      m_sprite.setTextureRect(m_animation[e_call].getFrame());
    }
    break;

    case e_active :
    {
      m_sprite.setTextureRect(m_animation[e_active].getFrame());
    }
    break;

    default : {} break;
  }
}
