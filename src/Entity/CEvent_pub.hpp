#ifndef CEVENT_PUB_HPP_
#define CEVENT_PUB_HPP_

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

    enum Estate {};

    enum EAnimation {};
    unsigned int m_nb_animation = 0;
};

#endif
