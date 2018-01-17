#include "CActor.hpp"

/*explicit*/ CActor::CActor(unsigned int indice)
{
  LOG("CActor Constructor\n");

  m_donneesInit.classe = "CActor";
  m_donneesInit.indice = (sf:: Uint16) indice;
  m_donnees.indice = (sf:: Uint16) indice;

  m_isCharacter = false;

  m_sprite.setOrigin(sf::Vector2f(20, 30));

  m_goal_point = sf::Vector2i(0, 0);
  m_stop = sf::Vector2f(0, 0);

  m_timer = 0.f;

  m_attack = false;

  setTexture();
}

/*explicit*/ CActor::CActor(struct DonneesInit donnees)
{
  LOG("CActor Constructor\n");

  m_donneesInit = donnees;
  m_donnees.indice = donnees.indice;

  m_isCharacter = false;

  m_sprite.setOrigin(sf::Vector2f(20.f, 30.f));

  m_timer = 0.f;
  m_attack = false;

  m_goal_point = sf::Vector2i(0, 0);
  m_stop = sf::Vector2f(0, 0);

  m_timer = 0.f;

  setPosition(sf::Vector2f(donnees.positionX, donnees.positionY));
  setTexture(donnees);
  setAnimation();
}

/*virtual*/ CActor::~CActor(void)
{
  LOG("CActor Destructor\n");
}

// donne la texture au personnage
void CActor::setTexture(void)
{
  sf::Color newColor, hairColor;

  switch(CRandom::intInRange(0,3)){
    case 0 :
    { //Normale
      newColor = sf::Color(254, 211, 186);
      m_donneesInit.textures[1] = 0;
      m_donneesInit.textures_color[1][0] = 254;
      m_donneesInit.textures_color[1][1] = 211;
      m_donneesInit.textures_color[1][2] = 186;

      switch(CRandom::intInRange(0,4)){
        case 0 :
        {
          hairColor = sf::Color(210, 160, 110); //Blond
          m_donneesInit.textures_color[0][0] = 210;
          m_donneesInit.textures_color[0][1] = 160;
          m_donneesInit.textures_color[0][2] = 110;
          break;
        }
        case 1 :
        {
          hairColor = sf::Color(50, 50, 50);  //Noir
          m_donneesInit.textures_color[0][0] = 50;
          m_donneesInit.textures_color[0][1] = 50;
          m_donneesInit.textures_color[0][2] = 50;
          break;
        }
        case 2 :
        {
          hairColor = sf::Color(140, 80, 60); //Chatain
          m_donneesInit.textures_color[0][0] = 140;
          m_donneesInit.textures_color[0][1] = 80;
          m_donneesInit.textures_color[0][2] = 60;
          break;
        }
        case 3 :
        {
          hairColor = sf::Color(80, 40, 20); //Brun
          m_donneesInit.textures_color[0][0] = 80;
          m_donneesInit.textures_color[0][1] = 40;
          m_donneesInit.textures_color[0][2] = 20;
          break;
        }
        default : break;
      }

      break;
    }
    case 1 :
    { //Jaune
      newColor = sf::Color(254, 235, 190);
      m_donneesInit.textures[1] = 0;
      m_donneesInit.textures_color[1][0] = 254;
      m_donneesInit.textures_color[1][1] = 235;
      m_donneesInit.textures_color[1][2] = 190;

      hairColor = sf::Color(50, 50, 50);  //Noir
      m_donneesInit.textures_color[0][0] = 50;
      m_donneesInit.textures_color[0][1] = 50;
      m_donneesInit.textures_color[0][2] = 50;
      break;
    }
    case 2 :
    { //Noire
      newColor = sf::Color(100, 80, 50);
      m_donneesInit.textures[1] = 0;
      m_donneesInit.textures_color[1][0] = 100;
      m_donneesInit.textures_color[1][1] = 80;
      m_donneesInit.textures_color[1][2] = 50;

      switch(CRandom::intInRange(0,1)){
        case 0 :
        {
          hairColor = sf::Color(50, 50, 50);  //Noir
          m_donneesInit.textures_color[0][0] = 50;
          m_donneesInit.textures_color[0][1] = 50;
          m_donneesInit.textures_color[0][2] = 50;
          break;
        }
        case 1 :
        {
          hairColor = sf::Color(80, 40, 20); //Brun
          m_donneesInit.textures_color[0][0] = 80;
          m_donneesInit.textures_color[0][1] = 40;
          m_donneesInit.textures_color[0][2] = 20;
          break;
        }
        default : break;
      }

      break;
    }
    case 3 :
    { //Pâle
      newColor = sf::Color(254, 230, 215);
      m_donneesInit.textures[1] = 0;
      m_donneesInit.textures_color[1][0] = 254;
      m_donneesInit.textures_color[1][1] = 230;
      m_donneesInit.textures_color[1][2] = 215;

      switch(CRandom::intInRange(0,4)){
        case 0 :
        {
          hairColor = sf::Color(140, 80, 60); //Chatain
          m_donneesInit.textures_color[0][0] = 140;
          m_donneesInit.textures_color[0][1] = 80;
          m_donneesInit.textures_color[0][2] = 60;
          break;
        }
        case 1 :
        {
          hairColor = sf::Color(200, 110, 50); //Roux
          m_donneesInit.textures_color[0][0] = 200;
          m_donneesInit.textures_color[0][1] = 110;
          m_donneesInit.textures_color[0][2] = 50;
          break;
        }
        case 2 :
        {
          hairColor = sf::Color(100, 40, 20); //Brun
          m_donneesInit.textures_color[0][0] = 100;
          m_donneesInit.textures_color[0][1] = 40;
          m_donneesInit.textures_color[0][2] = 20;
          break;
        }
        case 3 :
        {
          hairColor = sf::Color(50, 50, 50); //Noir
          m_donneesInit.textures_color[0][0] = 50;
          m_donneesInit.textures_color[0][1] = 50;
          m_donneesInit.textures_color[0][2] = 50;
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
  m_donneesInit.textures[0] = CRandom::intInRange(2, 9);
}

void CActor::setTexture(struct DonneesInit donnees)
{
  //Texture
  m_prerender.create(160, 80);

  m_prerender.clear(sf::Color::Transparent);

  sf::Sprite spr;
  //Body
  sf::Image i_Body = CResourceHolder::get().image(EImage_Name::e_Body_White);
  sf::Color newColor, hairColor;

  newColor = sf::Color(donnees.textures_color[1][0], donnees.textures_color[1][1], donnees.textures_color[1][2]);
  hairColor = sf::Color(donnees.textures_color[0][0], donnees.textures_color[0][1], donnees.textures_color[0][2]);

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
  size_t hair_nb = donnees.textures[0];
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

void CActor::input(void)
{
  //TEST
  int size_map_x = 2000;
  int size_map_y = 2000;

  if (!m_isCharacter) // pnj
  {
    m_donnees.keyLeft = m_donnees.keyRight = m_donnees.keyUp = m_donnees.keyDown = m_donnees.keyShift = false;

    if ((m_goal_point.x != (int) m_donnees.positionX || m_goal_point.y != (int) m_donnees.positionY) && m_goal_point != sf::Vector2i(0, 0)) // si point de destination
    {
      m_donnees.keyLeft = (m_goal_point.x < (int) m_donnees.positionX);
      m_donnees.keyRight = (m_goal_point.x > (int) m_donnees.positionX);
      m_donnees.keyUp = (m_goal_point.y < (int) m_donnees.positionY);
      m_donnees.keyDown = (m_goal_point.y > (int) m_donnees.positionY);

      if (CRandom::intInRange(0, 10) == 0){
        if (CRandom::intInRange(0, 20) == 0){
          m_stop.x = 1 - m_stop.x;
        }
        if (CRandom::intInRange(0, 20) == 0){
          m_stop.y = 1 - m_stop.y;
        }
      }

      if(m_stop.x)
        m_donnees.keyLeft = false;
      if(m_stop.x)
        m_donnees.keyRight = false;
      if(m_stop.y)
        m_donnees.keyUp = false;
      if(m_stop.y)
        m_donnees.keyDown = false;

    }
    else // si pas de point de destination
    {
      switch(CRandom::intInRange(0, 100))
      {
        case 0 : // gauche
        {
          m_donnees.keyLeft = true;
          break;
        }
        case 1 : // haut
        {
          m_donnees.keyUp = true;
          break;
        }
        case 2 : // droite
        {
          m_donnees.keyRight = true;
          break;
        }
        case 3 : // bas
        {
          m_donnees.keyDown = true;
          break;
        }
        case 4 : // bas
        {
          m_goal_point = sf::Vector2i(CRandom::intInRange(100, 1900), CRandom::intInRange(100, 900));
          break;
        }
        default: break;
      }
    }
  }
}

void CActor::update(bool isServer, float dt)
{

  switch (m_state)
  {
    case e_idle :
    {
      if(m_donnees.keyLeft || m_donnees.keyRight || m_donnees.keyUp || m_donnees.keyDown)
      {
        if (!m_donnees.keyShift)
          m_state = e_walk;
        else
          m_state = e_run;
      }

      if(m_donnees.mouseLeft)
        m_state = e_attack;

      if (!isServer)
      {
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

      if(m_donnees.mouseLeft)
        m_state = e_attack;

      break;
    }

    case e_walk :
    {
      sf::Vector2f position = sf::Vector2f(m_donnees.positionX, m_donnees.positionY);

      m_move_speed = WALK_SPEED;

      if(m_donnees.keyLeft){
        if((position.x - (m_move_speed * dt)) >= 0){
          position.x += -(m_move_speed * dt);
        }
      }


      if(m_donnees.keyRight){
        if(((position.x + m_move_speed * dt) < 2000)){
          position.x += m_move_speed * dt;
        }
      }

      if(!(m_donnees.keyRight && m_donnees.keyLeft))
      {
          if(m_donnees.keyLeft)  m_orientation = e_left;
          if(m_donnees.keyRight) m_orientation = e_right;
      }

      if(m_donnees.keyUp){
        if(((position.y - (m_move_speed * dt)) >= 0 )){
          position.y += -(m_move_speed * dt);
        }
      }

      if(m_donnees.keyDown){
        if(((position.y + m_move_speed * dt) < 2000)){
          position.y += m_move_speed * dt;
        }
      }



      if(!m_donnees.keyLeft && !m_donnees.keyRight && !m_donnees.keyUp && !m_donnees.keyDown)
        m_state = e_idle;
      else
        if(m_donnees.keyShift)
          m_state = e_run;


      if (position != getPosition())
      {
        // mise a jour de la position
        setPosition(position);
        m_knife.setPosition(position);

        if (!isServer)
        {
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
      }
      else
        m_state = e_idle;

      if (!isServer)
      {
        // centre la vue sur la position du personnage si c'est un character
        if (m_isCharacter)
        {
          CDisplay::getView()->setCenter(getPosition());
          CDisplay::getWindow()->setView(* CDisplay::getView());
        }
      }

      if(m_donnees.mouseLeft)
        m_state = e_attack;

      break;
    }

    case e_run :
    {
      sf::Vector2f position = sf::Vector2f(m_donnees.positionX, m_donnees.positionY);
      m_move_speed = RUN_SPEED;
      if(m_donnees.keyLeft) position.x += -(m_move_speed * dt);
      if(m_donnees.keyRight) position.x += m_move_speed * dt;
      if(!(m_donnees.keyRight && m_donnees.keyLeft))
      {
          if(m_donnees.keyLeft)  m_orientation = e_left;
          if(m_donnees.keyRight) m_orientation = e_right;
      }
      if(m_donnees.keyUp) position.y += -(m_move_speed * dt);
      if(m_donnees.keyDown) position.y += m_move_speed * dt;

      if(!m_donnees.keyLeft && !m_donnees.keyRight && !m_donnees.keyUp  && !m_donnees.keyDown)
        m_state = e_idle;
      else
        if(!m_donnees.keyShift)
          m_state = e_walk;


      if (position != getPosition())
      {
        // mise a jour de la position
        setPosition(position);
        m_knife.setPosition(position);

        if (!isServer)
        {
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
      }
      else
        m_state = e_idle;

      if (!isServer)
      {
        // centre la vue sur la position du personnage si c'est un character
        if (m_isCharacter)
        {
          CDisplay::getView()->setCenter(getPosition());
          CDisplay::getWindow()->setView(* CDisplay::getView());
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
      if (!m_attack){
        m_knife.attack();
        m_attack = true;
      }

      m_knife.update(false, dt);

      if (m_knife.isLoopDone()){
        m_attack = false;
        m_timer = 0.f;
        m_state = e_slow;
      }

      break;
    }

    case e_slow :
    {
      m_timer += dt;

      sf::Vector2f position = sf::Vector2f(m_donnees.positionX, m_donnees.positionY);

      m_move_speed = WALK_SPEED/2;

      if(m_donnees.keyLeft){
        if((position.x - (m_move_speed * dt)) >= 0){
          position.x += -(m_move_speed * dt);
        }
      }


      if(m_donnees.keyRight){
        if(((position.x + m_move_speed * dt) < 2000)){
          position.x += m_move_speed * dt;
        }
      }

      if(!(m_donnees.keyRight && m_donnees.keyLeft))
      {
          if(m_donnees.keyLeft)  m_orientation = e_left;
          if(m_donnees.keyRight) m_orientation = e_right;
      }

      if(m_donnees.keyUp){
        if(((position.y - (m_move_speed * dt)) >= 0 )){
          position.y += -(m_move_speed * dt);
        }
      }

      if(m_donnees.keyDown){
        if(((position.y + m_move_speed * dt) < 2000)){
          position.y += m_move_speed * dt;
        }
      }

      if (position != getPosition())
      {
        // mise a jour de la position
        setPosition(position);
        m_knife.setPosition(position);

        if (!isServer)
        {
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
      }

      if (!isServer)
      {
        // centre la vue sur la position du personnage si c'est un character
        if (m_isCharacter)
        {
          CDisplay::getView()->setCenter(getPosition());
          CDisplay::getWindow()->setView(* CDisplay::getView());
        }
      }

      if (m_timer > 1)
        m_state = e_idle;

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
      m_timer += dt;

      if (m_timer > 2)
        m_state = e_disappear;

      break;
    }

    case e_disappear :
    {

      break;
    }

    default : break;
  }
}

void CActor::setIsCharacter(bool isCharacter)
{
  m_isCharacter = isCharacter;
}
