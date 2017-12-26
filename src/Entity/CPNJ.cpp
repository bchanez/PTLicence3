#include "CPNJ.hpp"

/*explicit*/ CPNJ::CPNJ()
{
  LOG("CPNJ Constructor\n");

  m_sprite.setOrigin(sf::Vector2f(20, 30));

  m_state = e_idle;
  m_orientation = e_right;

  m_goal_point = sf::Vector2i(0, 0);
  m_stop = sf::Vector2f(1, 1);

  setTexture();
  setAnimation();
}

/*virtual*/ CPNJ::~CPNJ()
{
  LOG("CPNJ Destructor\n");
}

// donne la texture au pnj
void CPNJ::setTexture(void)
{
  m_prerender.create(160, 80);

  m_prerender.clear(sf::Color::Transparent);

  sf::Sprite spr;
  //Body
  sf::Image i_Body = CResourceHolder::get().image(EImage_Name::e_Body_White);
  sf::Color newColor, hairColor;

  switch(rand()%4){
    case 0 :
    { //Normale
      newColor = sf::Color(254, 211, 186);

      switch(rand()%4){
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

      switch(rand()%2){
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

      switch(rand()%5){
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

// definie les animations du pnj
void CPNJ::setAnimation(void)
{
  for (unsigned int i = 0; i < m_nb_animation ; ++i)
    m_animation.push_back(CAnimation());

  for (int i = 0; i < 4 ; ++i)
  {
    m_animation[e_walk_right].addFrame(sf::IntRect(i * 40, 0, 40, 40), 0.1f);
    m_animation[e_walk_left].addFrame(sf::IntRect(i * 40, 40, 40, 40), 0.1f);
  }
}

void CPNJ::update(float dt)
{
  switch (m_state)
  {
    case e_idle :
    {
      if (CRandom::intInRange(0, 1000) == 0)
      {
        m_goal_point = sf::Vector2i(CRandom::intInRange(100, 1820), CRandom::intInRange(100, 980));
        m_state = e_walk;
      }
      else if (CRandom::intInRange(0, 500) == 0)
      {
        m_orientation = 1 - m_orientation;
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
    }
    break;

    case e_walk :
    {
      m_move_speed = WALK_SPEED;
      /*if(m_goal_point.x < (int) m_position.x) {
        m_position.x += -(m_move_speed * dt);
        m_orientation = e_left;
      }
      if(m_goal_point.x > (int) m_position.x) {
        m_position.x += m_move_speed * dt;
        m_orientation = e_right;
      }
      if(m_goal_point.y < (int) m_position.y)
        m_position.y += -(m_move_speed * dt);
      if(m_goal_point.y > (int) m_position.y)
        m_position.y += m_move_speed * dt;*/

      //Nouveau système de déplacement un peu plus naturel
      sf::Vector2f direction = sf::Vector2f(0, 0);

      if(m_goal_point.x < (int) m_position.x)
        direction.x += -1;

      if(m_goal_point.x > (int) m_position.x)
        direction.x += 1;

      if(m_goal_point.y < (int) m_position.y)
        direction.y += -1;

      if(m_goal_point.y > (int) m_position.y)
        direction.y += 1;


      if (rand()%20 == 0){
        if (rand()%10 == 0) m_stop.x = 1 - m_stop.x;
        if (rand()%10 == 0) m_stop.y = 1 - m_stop.y;
      }

      if (direction.x == 1)
        m_orientation = e_right;
      if (direction.x == -1)
        m_orientation = e_left;

      m_position.x += (m_stop.x * direction.x * m_move_speed * dt);
      m_position.y += (m_stop.y * direction.y * m_move_speed * dt);

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
      {
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


      if((sf::Vector2i)m_position == m_goal_point){
        m_state = e_idle;
      }
    }
    break;

    case e_action :
    {

    }
    break;

    case e_run :
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
