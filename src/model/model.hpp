#ifndef MODEL_HPP
#define MODEL_HPP

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <SFML/Graphics/Rect.hpp>
#include <vector>


// Indexing in vectors is done accroding to defines! //
class Model
{
public:
    Model(unsigned nStates, const std::shared_ptr<const sf::Texture>& texture);
    // Get texture of current model
    const std::shared_ptr<const sf::Texture>& getTexture() const;
    // Get rectangle for current frame
    const std::vector<sf::IntRect>& getTextureRectSeries(unsigned state) const;
    // Pushes info about rectangle at given sate
    void pushTextureRect(const sf::IntRect& textureRect, unsigned state);
    size_t getNFrames(unsigned state) const;
    void setTexture(const std::shared_ptr<const sf::Texture>& texture);
private:
    // Multiple entries for one texture are unwanted
    std::shared_ptr<const sf::Texture> mTexture;
    // Consequent animation frames
    std::vector<std::vector<sf::IntRect> > mTextureRects;
};

#endif // MODEL_HPP
