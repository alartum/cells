#include "animationstate.hpp"
#include <stdexcept>
#define DEBUG
#include "../debug.h"

AnimationState::AnimationState(size_t nframes, double global_frames, bool is_random_frame) :
    std::vector<sf::IntRect>(nframes),
    animation_time_(global_frames),
    is_random_frame_(is_random_frame)
{
}

bool AnimationState::getIsRandomFrame() const{
    return is_random_frame_;
}
void AnimationState::setIsRandomFrame(bool value){
    is_random_frame_ = value;
}

size_t AnimationState::getAnimationTime() const{
    return animation_time_;
}

void AnimationState::setAnimationTime(size_t animation_time){
    animation_time_ = animation_time;
}

sf::IntRect& AnimationState::getRect(size_t frame){
    try{
        return at(frame);
    }
    catch(const std::out_of_range& oor){
        //PERROR("No texture rect for frame =  %lu", frame);
        return bad_rect_;
    }
}

const sf::IntRect& AnimationState::getRect(size_t frame) const{
    try{
        return at(frame);
    }
    catch(const std::out_of_range& oor){
        //PERROR("No texture rect for frame %lu", frame);
        if (size() > 0)
            return at(0);
        else
            return bad_rect_;
    }
}

void AnimationState::setName(const std::string& name){
    name_ = name;
}

const std::string& AnimationState::getName() const{
    return name_;
}
