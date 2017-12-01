#ifndef CEvent_HPP_
#define CEvent_HPP_

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

  private:

    enum Estate {};

    enum EAnimation {};
    unsigned int m_nb_animation = 0;
};

#endif
