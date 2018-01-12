#pragma once

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"

class CEvent: public CEntity
{

  public:

    explicit CEvent(void);
    virtual ~CEvent(void);

    virtual void setTexture(void) = 0;
    void setAnimation(void) override = 0;
    void input(void) override = 0;
    void update(float dt) override = 0;
    void serverUpdate(float dt) override = 0;

  protected:

    enum Estate {e_idle, e_call, e_active};

    enum EAnimation {};
    unsigned int m_nb_animation;
};
