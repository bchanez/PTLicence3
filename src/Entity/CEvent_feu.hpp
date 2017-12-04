#ifndef CEVENT_FEU_HPP_
#define CEVENT_FEU_HPP_

#include "CEvent.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"

class CEvent_feu: public CEvent
{

  public:

    explicit CEvent_feu(void);
    virtual ~CEvent_feu(void);

    void setTexture(void);
    void setAnimation(void);
    void update(float dt);

  private:

    enum Estate {};

    enum EAnimation {};
    unsigned int m_nb_animation = 0;
};

#endif
