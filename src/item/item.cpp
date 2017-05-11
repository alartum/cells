#include "item.hpp"
#include <iostream>
#define DEBUG
#include "../debug.h"
#include "../tileinfo/tile_ids.hpp"

Item::Item(const sf::Vector2f& position, size_t state) :
    mTickNo(0)
{
    setPosition(position);
    setState(STATE_UNDEFINED_ID);
}

Item::~Item()
{
}

void Item::setState(size_t state)
{
    mState = state;
    if (mModel){
        mAnimation = &mModel->getAnimation(mState);
        mIsRandomFrame = mAnimation->getIsRandomFrame();
        mAnimationTime = mAnimation->getAnimationTime();
        setTextureRect(mAnimation->getRect(mFrameNo));
        mFramesAmount = mAnimation->size();
    }
    else{
        mFramesAmount = 0;
        mAnimation = nullptr;
        mIsRandomFrame = false;
        mAnimationTime = 1;
        mTickNo = 0;
        mFrameNo = 0;
    }
}

void Item::nextFrame()
{
    if (!mAnimation)
        return;
    if (mFramesAmount == 0){
        mTickNo = 0;
        mFrameNo = 0;
        return;
    }
    mTickNo = (mTickNo + 1) % mAnimationTime;
    double frame_rate = (double)mAnimationTime / mFramesAmount;
    double temp_frame = mTickNo / frame_rate;
    if ((int)temp_frame != mFrameNo){
        mFrameNo = (int)temp_frame;
        setTextureRect(mAnimation->getRect(mFrameNo));
    }
}

Item& Item::operator = (const Item& other)
{
    mModel = other.mModel;
    mFrameNo = other.mFrameNo;
    mAnimation = other.mAnimation;
    mFramesAmount = other.mFramesAmount;
    mState = other.mState;

    return *this;
}

void Item::setModel(const std::shared_ptr<const Model>& model)
{
    mModel = model;
    setTexture(*(mModel->getTexture()));
}

std::shared_ptr<const Model> Item::getModel() const
{
    return mModel;
}

void Item::setFrame(size_t frame){
    mFrameNo = frame % mFramesAmount;
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
    if (mFramesAmount == 0){
        mTickNo = 0;
        mFrameNo = 0;
        return;
    }
    if (mIsRandomFrame){
        mTickNo  = rand() % mAnimationTime;
        double frame_rate = (double)mAnimationTime / mFramesAmount;
        mFrameNo = (int)(mTickNo / frame_rate);
    }
    else{
        mTickNo = 0;
        mFrameNo = 0;
    }
}

void Item::initState(){
    setState(0);
}

size_t Item::getState() const{
    return mState;
}

 size_t Item::getFrame() const{
     return mFrameNo;
 }
