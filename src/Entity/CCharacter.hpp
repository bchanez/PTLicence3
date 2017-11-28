#ifndef CCHARACTER_HPP_
#define CCHARACTER_HPP_

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/CInput.hpp"
#include <iostream>

class CCharacter : public CEntity
{

  public:

    CCharacter(void);
    virtual ~CCharacter(void);

    void setTexture(void);
    CInput& getInput(void);
    void update(float dt);

  protected:

  private:

    CInput m_input;
    enum Estate {e_idle, e_walk, e_run, e_action, e_dead, e_disappear};

};

#endif
