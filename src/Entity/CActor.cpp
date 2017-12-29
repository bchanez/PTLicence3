#include "CActor.hpp"

/*explicit*/ CActor::CActor(bool isCharacter)
{
  LOG("CActor Constructor\n");

  CRandom::init();

  m_isCharacter = isCharacter;

  m_key.left = m_key.right = m_key.up = m_key.down = m_key.shift = false;

  m_sprite.setOrigin(sf::Vector2f(20, 30));

  m_state = e_idle;
  m_orientation = e_right;

  m_goal_point = sf::Vector2i(0, 0);

  setTexture();
  setAnimation();
}

/*virtual*/ CActor::~CActor(void)
{
  LOG("CActor Destructor\n");
}

// donne la texture au personnage
void CActor::setTexture(void)
{
  m_prerender.create(160, 80);

  m_prerender.clear(sf::Color::Transparent);

  sf::Sprite spr;
  //Body
  sf::Image i_Body = CResourceHolder::get().image(EImage_Name::e_Body_White);
  sf::Color newColor, hairColor;

  switch(CRandom::intInRange(0,3)){
    case 0 :
    { //Normale
      newColor = sf::Color(254, 211, 186);

      switch(CRandom::intInRange(0,4)){
        case 0 :
        {
          hairColor = sf::Color(210, 160, 110); //Blond
          break;
        }
        case 1 :
        {
          hairColor = sf::Color(50, 50, 50);  //Noir
          break;
        }
        case 2 :
        {
          hairColor = sf::Color(140, 80, 60); //Chatain
          break;
        }
        case 3 :
        {
          hairColor = sf::Color(80, 40, 20); //Brun
          break;
        }
        default : break;
      }

      break;
    }
    case 1 :
    { //Jaune
      newColor = sf::Color(254, 235, 190);
      hairColor = sf::Color(50, 50, 50);  //Noir
      break;
    }
    case 2 :
    { //Noire
      newColor = sf::Color(100, 80, 50);

      switch(CRandom::intInRange(0,1)){
        case 0 :
        {
          hairColor = sf::Color(50, 50, 50);  //Noir
          break;
        }
        case 1 :
        {
          hairColor = sf::Color(80, 40, 20); //Brun
          break;
        }
        default : break;
      }

      break;
    }
    case 3 :
    { //Pâle
      newColor = sf::Color(254, 230, 215);

      switch(CRandom::intInRange(0,4)){
        case 0 :
        {
          hairColor = sf::Color(140, 80, 60); //Chatain
          break;
        }
        case 1 :
        {
          hairColor = sf::Color(200, 110, 50); //Roux
          break;
        }
        case 2 :
        {
          hairColor = sf::Color(100, 40, 20); //Brun
          break;
        }
        case 3 :
        {
          hairColor = sf::Color(50, 50, 50); //Noir
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
  size_t hair_nb = CRandom::intInRange(2, 9);
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

// definie les animations du personnage
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

void CActor::input(sf::Event * event)
{
  if (m_isCharacter) // character
  {
    if((* event).type == sf::Event::KeyPressed)
    {
      if ((* event).key.code == sf::Keyboard::Z
        || (* event).key.code == sf::Keyboard::W)
        m_key.up = true;

      if ((* event).key.code == sf::Keyboard::Q
        || (* event).key.code == sf::Keyboard::A)
        m_key.left = true;

      if ((* event).key.code == sf::Keyboard::S)
        m_key.down = true;

      if ((* event).key.code == sf::Keyboard::D)
        m_key.right = true;

      if ((* event).key.code == sf::Keyboard::LShift)
        m_key.shift = true;
    }

    if((* event).type == sf::Event::KeyReleased)
    {
      if ((* event).key.code == sf::Keyboard::Z
        || (* event).key.code == sf::Keyboard::W)
        m_key.up = false;

      if ((* event).key.code == sf::Keyboard::Q
        || (* event).key.code == sf::Keyboard::A)
        m_key.left = false;

      if ((* event).key.code == sf::Keyboard::S)
        m_key.down = false;

      if ((* event).key.code == sf::Keyboard::D)
        m_key.right = false;

      if ((* event).key.code == sf::Keyboard::LShift)
        m_key.shift = false;
    }
  }
  else if (!m_isCharacter) // pnj
  {
    m_key.left = m_key.right = m_key.up = m_key.down = m_key.shift = false;

    if ((m_goal_point.x != (int) m_position.x || m_goal_point.y != (int) m_position.y) && m_goal_point != sf::Vector2i(0, 0)) // si point de destination
    {
      if(m_goal_point.x < (int) m_position.x)
        m_key.left = CRandom::intInRange(0, 20) != 0;
      if(m_goal_point.x > (int) m_position.x)
        m_key.right = CRandom::intInRange(0, 20) != 0;
      if(m_goal_point.y < (int) m_position.y)
        m_key.up = CRandom::intInRange(0, 20) != 0;
      if(m_goal_point.y > (int) m_position.y)
        m_key.down = CRandom::intInRange(0, 20) != 0;
    }
    else // si pas de point de destination
    {
      switch(CRandom::intInRange(0, 100))
      {
        case 0 : // gauche
        {
          m_key.left = true;
          break;
        }
        case 1 : // haut
        {
          m_key.up = true;
          break;
        }
        case 2 : // droite
        {
          m_key.right = true;
          break;
        }
        case 3 : // bas
        {
          m_key.down = true;
          break;
        }
        default: break;
      }
    }
  }
}

void CActor::update(float dt)
{
  switch (m_state)
  {
    case e_idle :
    {
      if(m_key.left || m_key.right || m_key.up || m_key.down)
      {
        if (!m_key.shift)
          m_state = e_walk;
        else
          m_state = e_run;
      }

      // mise a jour de l'animation
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

      if (!m_isCharacter)
        if (CRandom::intInRange(0, 1000) == 0)
          m_goal_point = sf::Vector2i(CRandom::intInRange(100, 1820), CRandom::intInRange(100, 980));

    }
    break;

    case e_walk :
    {
      m_move_speed = WALK_SPEED;
      if(m_key.left) m_position.x += -(m_move_speed * dt);
      if(m_key.right) m_position.x += m_move_speed * dt;
      if(!(m_key.right && m_key.left))
      {
          if(m_key.left)  m_orientation = e_left;
          if(m_key.right) m_orientation = e_right;
      }
      if(m_key.up) m_position.y += -(m_move_speed * dt);
      if(m_key.down) m_position.y += m_move_speed * dt;

      if(!m_key.left && !m_key.right && !m_key.up  && !m_key.down)
        m_state = e_idle;
      else
        if(m_key.shift)
          m_state = e_run;


      if (m_position != m_sprite.getPosition())
      {
        // mise a jour de la position
        m_sprite.setPosition(m_position);

        // mise a jour de l'animation
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
      }
      else
        m_state = e_idle;

      // centre la vue sur la position du personnage si c'est un character
      if (m_isCharacter)
      {
        CDisplay::getView()->setCenter(m_position);
        CDisplay::getWindow()->setView(* CDisplay::getView());
      }
    }
    break;

    case e_run :
    {
      m_move_speed = RUN_SPEED;
      if(m_key.left) m_position.x += -(m_move_speed * dt);
      if(m_key.right) m_position.x += m_move_speed * dt;
      if(!(m_key.right && m_key.left))
      {
          if(m_key.left)  m_orientation = e_left;
          if(m_key.right) m_orientation = e_right;
      }
      if(m_key.up) m_position.y += -(m_move_speed * dt);
      if(m_key.down) m_position.y += m_move_speed * dt;

      if(!m_key.left && !m_key.right && !m_key.up  && !m_key.down)
        m_state = e_idle;
      else
        if(!m_key.shift)
          m_state = e_walk;

      if (m_position != m_sprite.getPosition())
      {
        // mise a jour de la position
        m_sprite.setPosition(m_position);

        // mise a jour de l'animation
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
      }
      else
        m_state = e_idle;

      // centre la vue sur la position du personnage si c'est un character
      if (m_isCharacter)
      {
        CDisplay::getView()->setCenter(m_position);
        CDisplay::getWindow()->setView(* CDisplay::getView());
      }
    }
    break;

    case e_action :
    {

    }
    break;

    case e_wander :
    {

    }
    break;

    case e_question :
    {

    }
    break;

    case e_dead :
    {

    }
    break;

    case e_disappear :
    {

    }
    break;

    default : {} break;
  }
}
