#pragma once

#include "CEvent.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"

class CEvent_pub: public CEvent
{

  public:

    explicit CEvent_pub(void);
    explicit CEvent_pub(struct DonneesInit donnees);
    virtual ~CEvent_pub(void);

    void setTexture(void) override;
    void setAnimation(void) override;
    void input(bool left, bool right, bool up, bool down, bool shift) override;
    void update(float dt) override;

  private:

    unsigned int m_nb_animation = 3;
};
