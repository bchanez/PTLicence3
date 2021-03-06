#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Tools/CDrawable.hpp"
#include "../Tools/CAnimation.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Tools/CRandom.hpp"
#include "../Tools/CCollision.hpp"
#include "../Server/CData.hpp"
#include "../CConfig.hpp"

#define WALK_SPEED 60
#define RUN_SPEED 120

class CEntity : public CDrawable
{

  public:
    explicit CEntity(void);
    virtual ~CEntity(void);

    sf::Vector2f getPosition(void);
    void setPosition(sf::Vector2f pos);

    virtual void setAnimation(void) = 0;

    virtual void update(bool isServer, float dt) = 0;
    virtual void input(void) = 0;

    struct DataInit getDataInit(void);
    struct Data getData(void);
    void setData(struct Data d);

    bool getIsAlive(void);
    void setIsAlive(bool isAlive);

  protected:

    struct DataInit m_dataInit;
    struct Data m_data;

    bool m_isAlive;

    unsigned int m_move_speed;

    enum Estate {e_idle};

    enum Eorientation {e_right, e_left};
    unsigned int m_orientation;

    enum EAnimation {};
    unsigned int m_nb_animation;
    std::vector<CAnimation> m_animation;

    std::vector<std::unique_ptr<CEntity>> * m_listEntities; //Each entity can access another entity
};
