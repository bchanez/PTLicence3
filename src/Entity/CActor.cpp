#include "CActor.hpp"

/*explicit*/ CActor::CActor(unsigned int index, std::vector<std::unique_ptr<CEntity>> * listEntities)
{
  LOG("CActor Constructor\n");

  m_listEntities = listEntities;

  m_dataInit.cclass = "CActor";
  m_dataInit.index = (sf:: Uint16) index;
  m_data.index = (sf:: Uint16) index;

  m_isCharacter = false;

  m_sprite.setOrigin(sf::Vector2f(20, 30));

  m_goal_point = sf::Vector2i(0, 0);
  m_stop = sf::Vector2f(0, 0);

  m_timer = 0.f;

  m_attack = false;
  m_mustDisappear = false;

  m_event = false;

  setTexture();
}

/*explicit*/ CActor::CActor(struct DataInit data)
{
  LOG("CActor Constructor\n");

  m_dataInit = data;
  m_data.index = data.index;

  m_isCharacter = false;

  m_sprite.setOrigin(sf::Vector2f(20.f, 30.f));

  m_goal_point = sf::Vector2i(0, 0);
  m_stop = sf::Vector2f(0, 0);

  m_timer = 0.f;

  m_attack = false;
  m_mustDisappear = false;

  m_event = false;

  setPosition(sf::Vector2f(data.positionX, data.positionY));
  setTexture(data);
  setAnimation();
}

/*virtual*/ CActor::~CActor(void)
{
  LOG("CActor Destructor\n");
}

// Set the character's texture
void CActor::setTexture(void)
{
  sf::Color newColor, hairColor;

  switch(CRandom::intInRange(0,3)){
    case 0 :
    { //Normal
      newColor = sf::Color(254, 211, 186);
      m_dataInit.textures[1] = 0;
      m_dataInit.textures_color[1][0] = 254;
      m_dataInit.textures_color[1][1] = 211;
      m_dataInit.textures_color[1][2] = 186;

      switch(CRandom::intInRange(0,4)){
        case 0 :
        {
          hairColor = sf::Color(210, 160, 110); //Blonde
          m_dataInit.textures_color[0][0] = 210;
          m_dataInit.textures_color[0][1] = 160;
          m_dataInit.textures_color[0][2] = 110;
          break;
        }
        case 1 :
        {
          hairColor = sf::Color(50, 50, 50);  //Black
          m_dataInit.textures_color[0][0] = 50;
          m_dataInit.textures_color[0][1] = 50;
          m_dataInit.textures_color[0][2] = 50;
          break;
        }
        case 2 :
        {
          hairColor = sf::Color(140, 80, 60); //Dark Blond
          m_dataInit.textures_color[0][0] = 140;
          m_dataInit.textures_color[0][1] = 80;
          m_dataInit.textures_color[0][2] = 60;
          break;
        }
        case 3 :
        {
          hairColor = sf::Color(80, 40, 20); //Brown
          m_dataInit.textures_color[0][0] = 80;
          m_dataInit.textures_color[0][1] = 40;
          m_dataInit.textures_color[0][2] = 20;
          break;
        }
        default : break;
      }

      break;
    }
    case 1 :
    { //Yellow
      newColor = sf::Color(254, 235, 190);
      m_dataInit.textures[1] = 0;
      m_dataInit.textures_color[1][0] = 254;
      m_dataInit.textures_color[1][1] = 235;
      m_dataInit.textures_color[1][2] = 190;

      hairColor = sf::Color(50, 50, 50);  //Black
      m_dataInit.textures_color[0][0] = 50;
      m_dataInit.textures_color[0][1] = 50;
      m_dataInit.textures_color[0][2] = 50;
      break;
    }
    case 2 :
    { //Black
      newColor = sf::Color(100, 80, 50);
      m_dataInit.textures[1] = 0;
      m_dataInit.textures_color[1][0] = 100;
      m_dataInit.textures_color[1][1] = 80;
      m_dataInit.textures_color[1][2] = 50;

      switch(CRandom::intInRange(0,1)){
        case 0 :
        {
          hairColor = sf::Color(50, 50, 50);  //Black
          m_dataInit.textures_color[0][0] = 50;
          m_dataInit.textures_color[0][1] = 50;
          m_dataInit.textures_color[0][2] = 50;
          break;
        }
        case 1 :
        {
          hairColor = sf::Color(80, 40, 20); //Brown
          m_dataInit.textures_color[0][0] = 80;
          m_dataInit.textures_color[0][1] = 40;
          m_dataInit.textures_color[0][2] = 20;
          break;
        }
        default : break;
      }

      break;
    }
    case 3 :
    { //Pale
      newColor = sf::Color(254, 230, 215);
      m_dataInit.textures[1] = 0;
      m_dataInit.textures_color[1][0] = 254;
      m_dataInit.textures_color[1][1] = 230;
      m_dataInit.textures_color[1][2] = 215;

      switch(CRandom::intInRange(0,4)){
        case 0 :
        {
          hairColor = sf::Color(140, 80, 60); //Dark Blond
          m_dataInit.textures_color[0][0] = 140;
          m_dataInit.textures_color[0][1] = 80;
          m_dataInit.textures_color[0][2] = 60;
          break;
        }
        case 1 :
        {
          hairColor = sf::Color(200, 110, 50); //Redhead
          m_dataInit.textures_color[0][0] = 200;
          m_dataInit.textures_color[0][1] = 110;
          m_dataInit.textures_color[0][2] = 50;
          break;
        }
        case 2 :
        {
          hairColor = sf::Color(100, 40, 20); //Brown
          m_dataInit.textures_color[0][0] = 100;
          m_dataInit.textures_color[0][1] = 40;
          m_dataInit.textures_color[0][2] = 20;
          break;
        }
        case 3 :
        {
          hairColor = sf::Color(50, 50, 50); //Black
          m_dataInit.textures_color[0][0] = 50;
          m_dataInit.textures_color[0][1] = 50;
          m_dataInit.textures_color[0][2] = 50;
          break;
        }
        case 4 :
        {
          hairColor = sf::Color(210, 160, 110); //Blond
          break;
        }
        default : break;
      }
      break;
    }
    default : break;
  }

  //Hair
  m_dataInit.textures[0] = CRandom::intInRange(2, 9);
}

void CActor::setTexture(struct DataInit data)
{
  //Texture
  m_prerender.create(160, 80);

  m_prerender.clear(sf::Color::Transparent);

  sf::Sprite spr;
  //Body
  sf::Image i_Body = CResourceHolder::get().image(EImage_Name::e_Body_White);
  sf::Color newColor, hairColor;

  newColor = sf::Color(data.textures_color[1][0], data.textures_color[1][1], data.textures_color[1][2]);
  hairColor = sf::Color(data.textures_color[0][0], data.textures_color[0][1], data.textures_color[0][2]);

  //newColor = sf::Color(200,200,200);

  for (int y = 0; y < (int)i_Body.getSize().y; y++){
    for (int x = 0; x < (int)i_Body.getSize().x; x++){
      if (i_Body.getPixel(x, y).a > 10){
        i_Body.setPixel(x, y, newColor);
      }
    }
  }

  sf::Texture t_Body;
  t_Body.loadFromImage(i_Body);

  spr.setTexture(t_Body);
  m_prerender.draw(spr);

  //Details
  i_Body = CResourceHolder::get().image(EImage_Name::e_Body_Details);
  t_Body.loadFromImage(i_Body);
  spr.setTexture(t_Body);
  m_prerender.draw(spr);

  //Hair
  size_t hair_nb = data.textures[0];
  sf::Image i_Hair = CResourceHolder::get().image((EImage_Name)hair_nb);


  for (int y = 0; y < (int)i_Hair.getSize().y; y++){
    for (int x = 0; x < (int)i_Hair.getSize().x; x++){
      if (i_Hair.getPixel(x, y).a > 10){
        i_Hair.setPixel(x, y, hairColor);
      }
    }
  }

  sf::Texture t_Hair;
  t_Hair.loadFromImage(i_Hair);

  spr.setTexture(t_Hair);
  m_prerender.draw(spr);

  //Details
  i_Hair = CResourceHolder::get().image((EImage_Name)(hair_nb+8));
  t_Hair.loadFromImage(i_Hair);
  spr.setTexture(t_Hair);
  m_prerender.draw(spr);

  //Clothes

  m_prerender.display();

  m_sprite.setTexture(m_prerender.getTexture());
}

// Define the character's animations
void CActor::setAnimation(void)
{
  for (unsigned int i = 0; i < m_nb_animation ; ++i)
    m_animation.push_back(CAnimation());

  for (int i = 0; i < 4 ; ++i)
  {
    m_animation[e_walk_right].addFrame(sf::IntRect(i * 40, 0, 40, 40), 0.1f);
    m_animation[e_walk_left].addFrame(sf::IntRect(i * 40, 40, 40, 40), 0.1f);
  }
}

void CActor::input(void)
{
  if (!m_isCharacter) // npc
  {
    m_data.keyLeft = m_data.keyRight = m_data.keyUp = m_data.keyDown = m_data.keyShift = false;

    if ((m_goal_point.x != (int) m_data.positionX || m_goal_point.y != (int) m_data.positionY) && m_goal_point != sf::Vector2i(0, 0)) // if destination point
    {
      m_data.keyLeft = (m_goal_point.x < (int) m_data.positionX);
      m_data.keyRight = (m_goal_point.x > (int) m_data.positionX);
      m_data.keyUp = (m_goal_point.y < (int) m_data.positionY);
      m_data.keyDown = (m_goal_point.y > (int) m_data.positionY);

      if (CRandom::intInRange(0, 10) == 0){
        if (CRandom::intInRange(0, 20) == 0){
          m_stop.x = 1 - m_stop.x;
        }
        if (CRandom::intInRange(0, 20) == 0){
          m_stop.y = 1 - m_stop.y;
        }
      }

      if(m_stop.x)
      {
        m_data.keyLeft = false;
        m_data.keyRight = false;
      }
      if(m_stop.y)
      {
        m_data.keyUp = false;
        m_data.keyDown = false;
      }

    }
    else // if no destination point
    {
      switch(CRandom::intInRange(0, 100))
      {
        case 0 : // left
        {
          m_data.keyLeft = true;
          break;
        }
        case 1 : // up
        {
          m_data.keyUp = true;
          break;
        }
        case 2 : // right
        {
          m_data.keyRight = true;
          break;
        }
        case 3 : // down
        {
          m_data.keyDown = true;
          break;
        }
        default: break;
      }
    }
  }
}

void CActor::update(bool isServer, float dt)
{
  switch (m_data.state)
  {
    case e_idle :
    {
      if(m_data.keyLeft || m_data.keyRight || m_data.keyUp || m_data.keyDown)
      {
        if (!m_data.keyShift)
          m_data.state = e_walk;
        else
          m_data.state = e_run;
      }

      if(m_data.mouseLeft)
        m_data.state = e_attack;


      if (isServer && !m_event && !m_isCharacter)
        if (CRandom::intInRange(0, 1000) == 0)
          m_goal_point = sf::Vector2i(CRandom::intInRange(SIZE_TILE, (SIZE_MAP_X-1)*SIZE_TILE), CRandom::intInRange(SIZE_TILE, (SIZE_MAP_Y-1)*SIZE_TILE));


      if (!isServer)
      {
        // Animation update
        if (m_orientation == e_right)
        {
          m_animation[e_walk_right].restart();
          m_sprite.setTextureRect(m_animation[e_walk_right].getCurrentFrame());
        }
        else if (m_orientation == e_left)
        {
          m_animation[e_walk_left].restart();
          m_sprite.setTextureRect(m_animation[e_walk_left].getCurrentFrame());
        }
      }

      break;
    }

    case e_walk :
    {
      sf::Vector2f position = sf::Vector2f(m_data.positionX, m_data.positionY);

      m_move_speed = WALK_SPEED;

      if(m_data.keyLeft)
        position.x += ((position.x - (m_move_speed * dt)) >= (SIZE_TILE/2)+1) ? -(m_move_speed * dt) : 0.f;

      if(m_data.keyRight)
        position.x += ((position.x + m_move_speed * dt) < (SIZE_MAP_X-1)*SIZE_TILE + (SIZE_TILE/2)) ? m_move_speed * dt : 0.f;

      if(m_data.keyUp)
        position.y += ((position.y - (m_move_speed * dt)) >= (SIZE_TILE/2)+1) ? -(m_move_speed * dt) : 0.f;

      if(m_data.keyDown)
        position.y += ((position.y + m_move_speed * dt) < (SIZE_MAP_Y-1)*SIZE_TILE + (SIZE_TILE/2)) ? m_move_speed * dt : 0.f;

      if(!(m_data.keyRight && m_data.keyLeft))
      {
          if(m_data.keyLeft)  m_orientation = e_left;
          if(m_data.keyRight) m_orientation = e_right;
      }

      if(position == getPosition())
        m_data.state = e_idle;
      else
        if(m_data.keyShift)
          m_data.state = e_run;

      if(m_data.mouseLeft)
        m_data.state = e_attack;


      if (position != getPosition())
      {
        //Position update
        setPosition(position);
        m_knife.setPosition(position);

        if (!isServer)
        {
          //Animation update
          if (m_orientation == e_right)
          {
            m_animation[e_walk_left].restart();
            m_sprite.setTextureRect(m_animation[e_walk_right].getFrame());
          }
          else if (m_orientation == e_left)
          {
            m_animation[e_walk_right].restart();
            m_sprite.setTextureRect(m_animation[e_walk_left].getFrame());
          }

          //Center view on character if not an NPC
          if (m_isCharacter)
          {
            CDisplay::getView()->setCenter(getPosition());
            CDisplay::getWindow()->setView(* CDisplay::getView());
          }
        }
      }

      break;
    }

    case e_run :
    {
      sf::Vector2f position = sf::Vector2f(m_data.positionX, m_data.positionY);

      m_move_speed = RUN_SPEED;

      if(m_data.keyLeft)
        position.x += ((position.x - (m_move_speed * dt)) >= (SIZE_TILE/2)+1) ? -(m_move_speed * dt) : 0.f;

      if(m_data.keyRight)
        position.x += ((position.x + m_move_speed * dt) < (SIZE_MAP_X-1)*SIZE_TILE  + (SIZE_TILE/2)) ? m_move_speed * dt : 0.f;

      if(m_data.keyUp)
        position.y += ((position.y - (m_move_speed * dt)) >= (SIZE_TILE/2)+1) ? -(m_move_speed * dt) : 0.f;

      if(m_data.keyDown)
        position.y += ((position.y + m_move_speed * dt) < (SIZE_MAP_Y-1)*SIZE_TILE + (SIZE_TILE/2)) ? m_move_speed * dt : 0.f;

      if(!(m_data.keyRight && m_data.keyLeft))
      {
          if(m_data.keyLeft)  m_orientation = e_left;
          if(m_data.keyRight) m_orientation = e_right;
      }

      if(position == getPosition())
        m_data.state = e_idle;
      else
        if(!m_data.keyShift)
          m_data.state = e_walk;

      if(m_data.mouseLeft)
        m_data.state = e_attack;

      if (position != getPosition())
      {
        // Update position
        setPosition(position);
        m_knife.setPosition(position);

        if (!isServer)
        {
          //Update animation
          if (m_orientation == e_right)
          {
            m_animation[e_walk_left].restart();
            m_sprite.setTextureRect(m_animation[e_walk_right].getFrame());
          }
          else if (m_orientation == e_left)
          {
            m_animation[e_walk_right].restart();
            m_sprite.setTextureRect(m_animation[e_walk_left].getFrame());
          }

          //Center view on character if not a NPC
          if (m_isCharacter)
          {
            CDisplay::getView()->setCenter(getPosition());
            CDisplay::getWindow()->setView(* CDisplay::getView());
          }
        }
      }
      break;
    }

    case e_action :
    {

      break;
    }

    case e_attack :
    {
      if(isServer)
      {
        for (unsigned int i = 0; i < (*m_listEntities).size(); ++i)
        {
          if ((*m_listEntities)[i]->getIsAlive() && getData().index != (*m_listEntities)[i]->getData().index)
            if (CCollision::collision(sf::FloatRect(getPosition().x - 20.f, getPosition().y - 20.f, 40.f, 40.f), (*m_listEntities)[i]->getPosition()))
            {
              dynamic_cast<CActor *>((*m_listEntities)[i].get())->m_data.state = e_dead;
            }
        }
      }

      if (!m_attack){
        m_knife.attack();
        m_attack = true;
      }

      m_knife.update(false, dt);

      if (m_knife.isLoopDone()){
        m_timer = 0.f;
        m_data.state = e_slow;
      }

      break;
    }

    case e_slow :
    {
      m_attack = false;

      m_timer += dt;

      sf::Vector2f position = sf::Vector2f(m_data.positionX, m_data.positionY);

      m_move_speed = WALK_SPEED/2;

      if(m_data.keyLeft)
        position.x += ((position.x - (m_move_speed * dt)) >= SIZE_TILE) ? -(m_move_speed * dt) : 0.f;

      if(m_data.keyRight)
        position.x += ((position.x + m_move_speed * dt) < (SIZE_MAP_X-1)*SIZE_TILE) ? m_move_speed * dt : 0.f;

      if(m_data.keyUp)
        position.y += ((position.y - (m_move_speed * dt)) >= SIZE_TILE) ? -(m_move_speed * dt) : 0.f;

      if(m_data.keyDown)
        position.y += ((position.y + m_move_speed * dt) < (SIZE_MAP_Y-1)*SIZE_TILE) ? m_move_speed * dt : 0.f;

      if(!(m_data.keyRight && m_data.keyLeft))
      {
          if(m_data.keyLeft)  m_orientation = e_left;
          if(m_data.keyRight) m_orientation = e_right;
      }

      if (position != getPosition())
      {
        //Update position
        setPosition(position);
        m_knife.setPosition(position);

        if (!isServer)
        {
          //Update animation
          if (m_orientation == e_right)
          {
            m_animation[e_walk_left].restart();
            m_sprite.setTextureRect(m_animation[e_walk_right].getFrame());
          }
          else if (m_orientation == e_left)
          {
            m_animation[e_walk_right].restart();
            m_sprite.setTextureRect(m_animation[e_walk_left].getFrame());
          }

          //Center view on character if not a NPC
          if (m_isCharacter)
          {
            CDisplay::getView()->setCenter(getPosition());
            CDisplay::getWindow()->setView(* CDisplay::getView());
          }
        }
      }

      if (m_timer > 1)
        m_data.state = e_idle;

      break;
    }

    case e_wander :
    {

      break;
    }

    case e_question :
    {

      break;
    }

    case e_dead :
    {
      setIsAlive(false);
      m_goal_point = sf::Vector2i(getPosition());

      m_timer += dt;

      if (m_timer > 2)
        m_data.state = e_disappear;

      break;
    }

    case e_disappear :
    {
      m_mustDisappear = true;
      break;
    }

    default : break;
  }
}

void CActor::setIsCharacter(bool isCharacter)
{
  m_isCharacter = isCharacter;
  m_data.keyLeft = m_data.keyRight = m_data.keyUp = m_data.keyDown = m_data.keyShift = m_data.mouseLeft = false;
}

bool CActor::getMustDisappear(void)
{
  return m_mustDisappear;
}

void CActor::setGoalPoint(sf::Vector2i dot)
{
  m_goal_point = dot;
}

sf::Vector2i CActor::getGoalPoint(void)
{
  return m_goal_point;
}

void CActor::setEvent(bool event)
{
  m_event = event;
}

bool CActor::getEvent(void)
{
  return m_event;
}
