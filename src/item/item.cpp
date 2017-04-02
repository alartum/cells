#include "item.hpp"
#include <iostream>

Item::Item(const std::shared_ptr<const Model>& model, unsigned state,
           const sf::Vector2f& position) :
    mModel(model),
    mState(state)
{
    setTexture(*mModel->getTexture());
    setState(0);
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
    mMaxFrameNo = mModel->getNFrames(mState) - 1;
    mFrames = &mModel->getTextureRectSeries(mState),
    setTextureRect((*mFrames)[mFrameNo]);
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
