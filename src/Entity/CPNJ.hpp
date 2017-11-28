#ifndef CPNJ_HPP_
#define CPNJ_HPP_

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include <iostream>
#include <time.h>

class CPNJ : public CEntity
{
  public:

    explicit CPNJ();
    virtual ~CPNJ();

    void update(float dt);

  protected:

  private:

    void IA();

    enum state {idle, walk, wander, action, question, run, dead, disappear};
};

#endif
