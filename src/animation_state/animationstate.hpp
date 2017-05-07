#ifndef ANIMATIONSTATE_HPP
#define ANIMATIONSTATE_HPP

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <string>

class AnimationState : public std::vector<sf::IntRect>
{
public:
    AnimationState(size_t nframes = 0, double global_frames = 1, bool is_random_frame = false);
    bool getIsRandomFrame() const;
    void setIsRandomFrame(bool value);
    size_t getAnimationTime() const;
    void   setAnimationTime(size_t animation_time);
    void setName(const std::string& name);
    const std::string& getName() const;
    // Exception handling version of at
    sf::IntRect& getRect(size_t frame);
    const sf::IntRect& getRect(size_t frame) const;
private:
    std::string mName;
    // Is it allowed to start animation from random frame
    bool mIsRandomFrame;
    // Number of global animation frames (provided by field)
    // we want to play the animation for
    //
    // Example:
    //    mGlobalFrames = 2
    //    animationTime = 8 (provided by ModelManager)
    //
    //    So, we want the animation to repeat with
    //    period of 2*8 = 16 basic ticks
    size_t mAnimationTime;
    // For error handling
    sf::IntRect mBadRect;
};

#endif // ANIMATIONSTATE_HPP
