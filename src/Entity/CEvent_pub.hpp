#pragma once

#include "CEvent.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"

class CEvent_pub: public CEvent
{

  public:

    explicit CEvent_pub(unsigned int index, std::vector<std::unique_ptr<CEntity>> * listEntities);
    explicit CEvent_pub(struct DataInit data);
    virtual ~CEvent_pub(void);

    void setTexture(void) override;
    void setAnimation(void) override;
    void input(void) override;
    void update(bool isServer, float dt) override;

  private:

    unsigned int m_nb_animation = 3;
};
