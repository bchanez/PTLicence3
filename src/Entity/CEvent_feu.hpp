#pragma once

#include "CEvent.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"

class CEvent_feu: public CEvent
{

  public:

    explicit CEvent_feu(void);
    virtual ~CEvent_feu(void);

    void setTexture(void) override;
    void setAnimation(void) override;
    void input(void) override;
    void update(float dt) override;
    void serverUpdate(float dt) override;

  private:

    enum Estate {};

    enum EAnimation {};
    unsigned int m_nb_animation = 0;
};
