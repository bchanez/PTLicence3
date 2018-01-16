#pragma once

#include "CEvent.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"

class CEvent_pub: public CEvent
{

  public:

    explicit CEvent_pub(unsigned int indice);
    explicit CEvent_pub(struct DonneesInit donnees);
    virtual ~CEvent_pub(void);

    void setTexture(void) override;
    void setAnimation(void) override;
    void input(void) override;
    void update(bool isServer, float dt) override;

  private:

    unsigned int m_nb_animation = 3;
};
