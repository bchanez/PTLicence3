#pragma once

#include "CEvent.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"

class CEvent_pub: public CEvent
{

  public:

    explicit CEvent_pub(void);
    virtual ~CEvent_pub(void);

    void setTexture(void);
    void setAnimation(void);
    void update(float dt);

  private:

    unsigned int m_nb_animation = 3;
};
