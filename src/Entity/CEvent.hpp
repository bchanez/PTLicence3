#ifndef CEVENT_HPP_
#define CEVENT_HPP_

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

    enum Estate {};

    enum EAnimation {};
    unsigned int m_nb_animation = 0;
};

#endif
