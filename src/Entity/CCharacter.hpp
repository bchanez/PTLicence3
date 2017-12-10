#pragma once

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/CInput.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Tools/CDisplay.hpp"
#include <math.h>

class CCharacter : public CEntity
{

  public:

    explicit CCharacter(void);
    virtual ~CCharacter(void);

    void setTexture(void) override;
    void setAnimation(void);
    CInput& getInput(void);
    void update(float dt) override;

  private:

    CInput m_input;
    enum Estate {e_idle, e_walk, e_run, e_action, e_dead, e_disappear};

    enum EAnimation {e_walk_right, e_walk_left};
    unsigned int m_nb_animation = 2;
};
