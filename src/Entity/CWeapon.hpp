#pragma once

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Tools/CDisplay.hpp"

class CWeapon : public CEntity
{
  public:

    explicit CWeapon(void);
    virtual ~CWeapon(void);

    void setTexture(void);
    void setAnimation(void) override;
    void input(void);
    void update(bool isServer, float dt) override;

    void attack(void);
    bool isLoopDone(void);

  private:

    bool m_loop;

    unsigned int m_nb_animation = 5;
    bool m_attack;
};
