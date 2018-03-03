#include "CEvent_pub.hpp"

/*explicit*/ CEvent_pub::CEvent_pub(unsigned int index, std::vector<std::unique_ptr<CEntity>> * listEntities)
{
  LOG("CEvent_pub Constructor\n");

  m_listEntities = listEntities;

  m_dataInit.cclass = "CEvent_pub";
  m_dataInit.index = index;
  m_data.index = index;

  m_sprite.setOrigin(sf::Vector2f(100, 100));

  m_data.state = e_idle;
}

/*explicit*/ CEvent_pub::CEvent_pub(struct DataInit data)
{
  LOG("CEvent_pub Constructor\n");

  m_dataInit.index = data.index;
  m_data.index = data.index;

  m_sprite.setOrigin(sf::Vector2f(100, 100));

  m_data.state = e_idle;

  setPosition(sf::Vector2f(data.positionX, data.positionY));
  setTexture();
  setAnimation();
}

/*virtual*/ CEvent_pub::~CEvent_pub(void)
{
  LOG("CEvent_pub Destructor\n");
}

// Give the event a texture
void CEvent_pub::setTexture(void)
{
  m_sprite.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Pub));
}

//Define the event's textures
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

  switch (m_data.state)
  {
    case e_idle :
    {
      if(isServer)
      {
        if (CRandom::intInRange(0, 3000) == 0)
          m_data.state = e_call;
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
            m_data.state = e_active;

        for (unsigned int i = 0; i < (*m_listEntities).size(); ++i)
        {
          if ((*m_listEntities)[i]->getIsAlive())
          {
            if (!dynamic_cast<CActor *>((*m_listEntities)[i].get())->getEvent()
              && CCollision::collision(sf::FloatRect(getPosition().x - 150.f, getPosition().y - 160.f, 300.f, 320.f), (*m_listEntities)[i]->getPosition()))
            {
              dynamic_cast<CActor *>((*m_listEntities)[i].get())->setEvent(true);
              dynamic_cast<CActor *>((*m_listEntities)[i].get())->setGoalPoint(sf::Vector2i(CRandom::floatInRange(getPosition().x - 70.f, getPosition().x + 100.f), CRandom::floatInRange(getPosition().y, getPosition().y + 40.f)));
            }
            else if (dynamic_cast<CActor *>((*m_listEntities)[i].get())->getEvent())
            {
              if (CRandom::intInRange(0, 1000) == 0)
                dynamic_cast<CActor *>((*m_listEntities)[i].get())->setGoalPoint(sf::Vector2i(CRandom::floatInRange(getPosition().x - 70.f, getPosition().x + 100.f), CRandom::floatInRange(getPosition().y, getPosition().y + 40.f)));
            }
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
        {
          m_data.state = e_idle;

          for (unsigned int i = 0; i < (*m_listEntities).size(); ++i)
            if ((*m_listEntities)[i]->getIsAlive())
              dynamic_cast<CActor *>((*m_listEntities)[i].get())->setEvent(false);
        }


        for (unsigned int i = 0; i < (*m_listEntities).size(); ++i)
        {
          if ((*m_listEntities)[i]->getIsAlive())
            if (dynamic_cast<CActor *>((*m_listEntities)[i].get())->getEvent())
            {
              if (CRandom::intInRange(0, 1000) == 0)
                dynamic_cast<CActor *>((*m_listEntities)[i].get())->setGoalPoint(sf::Vector2i(CRandom::floatInRange(getPosition().x - 70.f, getPosition().x + 100.f), CRandom::floatInRange(getPosition().y, getPosition().y + 40.f)));
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
