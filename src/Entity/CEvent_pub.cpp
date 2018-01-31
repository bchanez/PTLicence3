#include "CEvent_pub.hpp"

/*explicit*/ CEvent_pub::CEvent_pub(unsigned int indice, std::vector<std::unique_ptr<CEntity>> * listEntite)
{
  LOG("CEvent_pub Constructor\n");

  m_listEntite = listEntite;

  m_donneesInit.classe = "CEvent_pub";
  m_donneesInit.indice = indice;
  m_donnees.indice = indice;

  m_sprite.setOrigin(sf::Vector2f(100, 100));

  m_donnees.state = e_idle;
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
  (void) dt;

  switch (m_donnees.state)
  {
    case e_idle :
    {
      if(isServer)
      {
        if (CRandom::intInRange(0, 1000) == 0)
          m_donnees.state = e_call;
      }
      else
      {
        m_sprite.setTextureRect(m_animation[e_idle].getFrame());
      }
    }
    break;

    case e_call :
    {
      if(isServer)
      {
        if (CRandom::intInRange(0, 1000) == 0)
            m_donnees.state = e_active;

        for (unsigned int i = 0; i < (*m_listEntite).size(); ++i)
        {
          if ((*m_listEntite)[i]->getIsAlive())
            if (CCollision::collision(sf::FloatRect(getPosition().x - 200.f, getPosition().y - 160.f, 400.f, 320.f), (*m_listEntite)[i]->getPosition()))
            {
              dynamic_cast<CActor *>((*m_listEntite)[i].get())->setGoalPoint(sf::Vector2i(CRandom::floatInRange(getPosition().x - 100.f, getPosition().x + 100.f), CRandom::floatInRange(getPosition().y, getPosition().y + 60.f)));
            }
        }
      }
      else
      {
        m_sprite.setTextureRect(m_animation[e_call].getFrame());
      }
    }
    break;

    case e_active :
    {
      if(isServer)
      {
        if (CRandom::intInRange(0, 2000) == 0)
            m_donnees.state = e_idle;

        for (unsigned int i = 0; i < (*m_listEntite).size(); ++i)
        {
          if ((*m_listEntite)[i]->getIsAlive())
            if (CCollision::collision(sf::FloatRect(getPosition().x - 100.f, getPosition().y, 200.f, 60.f), (*m_listEntite)[i]->getPosition()))
            {
                dynamic_cast<CActor *>((*m_listEntite)[i].get())->setGoalPoint(sf::Vector2i(CRandom::floatInRange(getPosition().x - 100.f, getPosition().x + 100.f), CRandom::floatInRange(getPosition().y, getPosition().y + 60.f)));
            }
        }
      }
      else
      {
        m_sprite.setTextureRect(m_animation[e_active].getFrame());
      }
    }
    break;

    default : {} break;
  }
}
