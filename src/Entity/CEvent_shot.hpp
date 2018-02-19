#pragma once

#include "CEvent.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"

class CEvent_shot: public CEvent
{

  public:

    explicit CEvent_shot(void);
    virtual ~CEvent_shot(void);

    void setTexture(void) override;
    void setAnimation(void) override;
    void input(void) override;
    void update(bool isServer, float dt) override;

  private:

    enum Estate {};

    enum EAnimation {};
    unsigned int m_nb_animation = 0;
};
