#include "item.hpp"
#include <iostream>

Item::Item(const sf::Vector2f& position, unsigned state)
{
    setState(state);
    setPosition(position);
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
        mMaxFrameNo = mModel->getNFrames(mState) - 1;
        mFrames = &mModel->getTextureRectSeries(mState),
        setTextureRect((*mFrames)[mFrameNo]);
    }
    else{
        mMaxFrameNo = 0;
    }
}

void Item::nextFrame()
{
    if (mFrameNo == mMaxFrameNo)
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
