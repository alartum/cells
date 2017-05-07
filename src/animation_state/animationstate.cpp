#include "animationstate.hpp"
#include <stdexcept>
#define DEBUG
#include "debug.h"

AnimationState::AnimationState(size_t nframes, double global_frames, bool is_random_frame) :
    std::vector<sf::IntRect>(nframes),
    mAnimationTime(global_frames),
    mIsRandomFrame(is_random_frame)
{
}

bool AnimationState::getIsRandomFrame() const{
    return mIsRandomFrame;
}
void AnimationState::setIsRandomFrame(bool value){
    mIsRandomFrame = value;
}

size_t AnimationState::getAnimationTime() const{
    return mAnimationTime;
}

void AnimationState::setAnimationTime(size_t animation_time){
    mAnimationTime = animation_time;
}

sf::IntRect& AnimationState::getRect(size_t frame){
    try{
        return at(frame);
    }
    catch(const std::out_of_range& oor){
        PERROR("No texture rect for frame =  %lu", frame);
        return mBadRect;
    }
}

const sf::IntRect& AnimationState::getRect(size_t frame) const{
    try{
        return at(frame);
    }
    catch(const std::out_of_range& oor){
        PERROR("No texture rect for frame =  %lu", frame);
        return mBadRect;
    }
}

void AnimationState::setName(const std::string& name){
    mName = name;
}

const std::string& AnimationState::getName() const{
    return mName;
}
