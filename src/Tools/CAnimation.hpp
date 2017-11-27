#ifndef CANIMATION_HPP_
#define CANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

class CAnimation
{
    struct Frame
    {
        Frame(const sf::IntRect& frame, float timeToNextFrame)
        :   frame           (frame)
        ,   timeToNextFrame (timeToNextFrame) {}

        sf::IntRect frame;
        float       timeToNextFrame;
    };

    public:
      CAnimation();
      ~CAnimation();

      void addFrame (const sf::IntRect& frame, float timeToNextFrame);
      const sf::IntRect getFrame();

    private:
        std::vector<Frame> m_frames;

        sf::Clock   m_timer;
        unsigned    m_currentFrame      = 0;
        float       m_longestFrameTime  = 0;
};

#endif
