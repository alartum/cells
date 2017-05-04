#include "model.hpp"
#include <iostream>

Model::Model(unsigned nStates, const std::shared_ptr<const sf::Texture>& texture) :
    mTexture(texture),
    mTextureRects(nStates)
{
}

const std::shared_ptr<const sf::Texture> &Model::getTexture() const
{
    return mTexture;
}

const std::vector<sf::IntRect>& Model::getTextureRectSeries(unsigned state) const
{
    try{
        return mTextureRects.at(state);
    }
    catch (const std::out_of_range& oor){
        std::cerr << "[Model] No frame rectangle series for state =  " << state << "\n";
        return mTextureRects[0];
    }
}

void Model::pushTextureRect(const sf::IntRect& textureRect, unsigned state)
{
    mTextureRects[state].push_back(textureRect);
}

size_t Model::getNFrames(unsigned state) const
{
    return mTextureRects[state].size();
}

void Model::setTexture(const std::shared_ptr<const sf::Texture>& texture)
{
    mTexture = texture;
    mTextureRects.clear();
}
