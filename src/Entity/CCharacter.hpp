#ifndef CCHARACTER_HPP_
#define CCHARACTER_HPP_

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/CInput.hpp"
#include <iostream>

class CCharacter : public CEntity
{

  public:

    CCharacter();
    ~CCharacter();

    CInput& getInput();
    void getEvent(float dt);
    void update(float dt);

  protected:

  private:

    CInput m_input;
    enum state {idle, walk, run, action, dead, disappear};

};

#endif
