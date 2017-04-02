#include "model.hpp"

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
    return mTextureRects[state];
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
