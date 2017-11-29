#ifndef CANIMATION_HPP_
#define CANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "DEBUG.hpp"

class CAnimation
{
    struct Frame
    {
      Frame(const sf::IntRect f, float t)
      {
        frame = f;
        timeToNextFrame = t;
      }

      sf::IntRect frame;
      float timeToNextFrame;
    };

    public:
      explicit CAnimation();
      virtual ~CAnimation();

      void addFrame(const sf::IntRect& frame, float timeToNextFrame);
      const sf::IntRect getFrame();
      const sf::IntRect getCurrentFrame();
      void restart(void);

    private:
        std::vector<Frame> m_frames;

        sf::Clock m_timer;

        unsigned int m_currentFrame;
};

#endif
