#ifndef CCHARACTER_HPP_
#define CCHARACTER_HPP_

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/CInput.hpp"
#include "../Tools/CAnimation.hpp"
#include <iostream>
#include <vector>

class CCharacter : public CEntity
{

  public:

    explicit CCharacter(void);
    virtual ~CCharacter(void);

    void setTexture(void);
    void setAnimation(void);
    CInput& getInput(void);
    void update(float dt);

  protected:

  private:

    CInput m_input;
    enum Estate {e_idle, e_walk, e_run, e_action, e_dead, e_disappear};

    const int m_nb_animation = 2;
    enum EAnimation {e_walk_right, e_walk_left};
    std::vector<CAnimation> m_animation;
};

#endif
