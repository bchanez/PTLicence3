#ifndef CEVENT_CONCERT_HPP_
#define CEVENT_CONCERT_HPP_

#include "CEvent.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"

class CEvent_concert: public CEvent
{

  public:

    explicit CEvent_concert(void);
    virtual ~CEvent_concert(void);

    void setTexture(void);
    void setAnimation(void);
    void update(float dt);

  private:

    enum Estate {};

    enum EAnimation {};
    unsigned int m_nb_animation = 0;
};

#endif
