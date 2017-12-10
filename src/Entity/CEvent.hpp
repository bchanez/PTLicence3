#pragma once

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"

class CEvent: public CEntity
{

  public:

    explicit CEvent(void);
    virtual ~CEvent(void);

    void setTexture(void);
    void setAnimation(void);
    void update(float dt);

  protected:

    enum Estate {e_idle, e_call, e_active};

    enum EAnimation {};
    unsigned int m_nb_animation;
};
