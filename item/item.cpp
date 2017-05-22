#include "item.hpp"
#include <iostream>
#define DEBUG
#include "../debug.h"

Item::Item(const sf::Vector2f& position, size_t state) :
    tick_no_(0)
{
    setPosition(position);
    setState(state);
}

Item::~Item()
{
}

void Item::setState(size_t state)
{
    state_ = state;
    if (model_){
        animation_ = &model_->getAnimation(state_);
        is_random_frame_ = animation_->getIsRandomFrame();
        animation_time_ = animation_->getAnimationTime();
        setTextureRect(animation_->getRect(frame_no_));
        frames_amount_ = animation_->size();
    }
    else{
        frames_amount_ = 0;
        animation_ = nullptr;
        is_random_frame_ = false;
        animation_time_ = 1;
        tick_no_ = 0;
        frame_no_ = 0;
    }
}

void Item::nextFrame()
{
    if (!animation_)
        return;
    if (frames_amount_ == 0){
        tick_no_ = 0;
        frame_no_ = 0;
        return;
    }
    tick_no_ = (tick_no_ + 1) % animation_time_;
    double frame_rate = (double)animation_time_ / frames_amount_;
    double temp_frame = tick_no_ / frame_rate;
    if (static_cast<size_t>(temp_frame) != frame_no_){
        frame_no_ = static_cast<size_t>(temp_frame);
        setTextureRect(animation_->getRect(frame_no_));
    }
}

Item& Item::operator = (const Item& other)
{
    model_ = other.model_;
    frame_no_ = other.frame_no_;
    animation_ = other.animation_;
    frames_amount_ = other.frames_amount_;
    state_ = other.state_;

    return *this;
}

void Item::setModel(const std::shared_ptr<const Model>& model)
{
    model_ = model;
    setTexture(*(model_->getTexture()));
}

std::shared_ptr<const Model> Item::getModel() const
{
    return model_;
}

void Item::setFrame(size_t frame){
    frame_no_ = frame % frames_amount_;
}

/*
void Item::calcSpritePosition(sf::Vector2u& tileSize) {
    sf::Vector2f ent_pos(mLatticePosition.y * tileSize.x, mLatticePosition.x * tileSize.y);
    setPosition(ent_pos);
}

const sf::Vector2u& Item::getLatticePosition() const {
    return mLatticePosition;
}
*/

void Item::initFrame(){
    if (frames_amount_ == 0){
        tick_no_ = 0;
        frame_no_ = 0;
        return;
    }
    if (is_random_frame_){
        tick_no_  = rand() % animation_time_;
        double frame_rate = (double)animation_time_ / frames_amount_;
        frame_no_ = (int)(tick_no_ / frame_rate);
    }
    else{
        tick_no_ = 0;
        frame_no_ = 0;
    }
}

void Item::initState(){
    setState(0);
}

size_t Item::getState() const{
    return state_;
}

 size_t Item::getFrame() const{
     return frame_no_;
 }
