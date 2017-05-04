#include "item.hpp"
#include <iostream>
#define DEBUG
#include "../debug.h"

Item::Item(const sf::Vector2u& latticePosition, unsigned state) : mLatticePosition(latticePosition)
{
    setState(state);
    //setPosition(position);
}

Item::~Item()
{
}

void Item::setState(unsigned state)
{
    mState = state;
    mIsUpdated = true;
    mFrameNo = 0;
    if (mModel){
        mFrames = &mModel->getTextureRectSeries(mState);
        mMaxFrameNo = mFrames->size() - 1;
        setTextureRect((*mFrames)[mFrameNo]);
    }
    else{
        mMaxFrameNo = 0;
    }
}

void Item::nextFrame()
{
    if (!mModel)
        return;
    if (mFrameNo >= mMaxFrameNo)
        mFrameNo = 0;
    else
        mFrameNo++;
    setTextureRect((*mFrames)[mFrameNo]);
}

Item& Item::operator = (const Item& other)
{
    mModel = other.mModel;
    mFrameNo = other.mFrameNo;
    mFrames = other.mFrames;
    mMaxFrameNo = other.mMaxFrameNo;
    mState = other.mState;
    mTypeID = other.mTypeID;
    mIsUpdated = false;

    return *this;
}

void Item::setModel(const std::shared_ptr<const Model>& model)
{
    mModel = model;
    setTexture(*mModel->getTexture());
    setState(0);
}

std::shared_ptr<const Model> Item::getModel() const
{
    return mModel;
}

void Item::setFrame(unsigned frame){
    if (frame > mMaxFrameNo){
        std::cerr << "[Item] Rejected attempt to set invalid frame = " << frame << "\n";
    }
    else
        mFrameNo = frame;
}

void Item::calcSpritePosition(sf::Vector2u& tileSize) {
    sf::Vector2f ent_pos(mLatticePosition.y * tileSize.x, mLatticePosition.x * tileSize.y);
    setPosition(ent_pos);
}

const sf::Vector2u& Item::getLatticePosition() const {
    return mLatticePosition;
}

