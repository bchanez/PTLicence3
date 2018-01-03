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
    void input(bool left, bool right, bool up, bool down, bool shift) override;
    void update(float dt) override;

  private:

    enum Estate {};

    enum EAnimation {};
    unsigned int m_nb_animation = 0;
};
