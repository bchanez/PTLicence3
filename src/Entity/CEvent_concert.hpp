#pragma once

#include "CEvent.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"

class CEvent_concert: public CEvent
{

  public:

    explicit CEvent_concert(void);
    virtual ~CEvent_concert(void);

    void setTexture(void) override;
    void setAnimation(void) override;
    void update(float dt) override;

  private:

    enum Estate {};

    enum EAnimation {};
    unsigned int m_nb_animation = 0;
};
