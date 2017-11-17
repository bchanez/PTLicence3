#ifndef CCHARACTER_
#define CCHARACTER_

#include "CEntity.hpp"
#include "ResourceManager/CResourceHolder.hpp"

class CCharacter : public CEntity{

public :

  CCharacter();

  void update();

protected :

  enum s {idle, walk};
  int m_speed;

private :

};



#endif
