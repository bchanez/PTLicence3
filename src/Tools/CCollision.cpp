#include "CCollision.hpp"

namespace CCollision
{
  bool collision(sf::FloatRect box, sf::Vector2f dot)
  {
    return box.contains(dot);
  }
}
