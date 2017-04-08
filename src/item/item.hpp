#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "../model/model.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class Item : public sf::Sprite
{
private:
    // Max frame number. Needed as the Object doesn't necessary use all the
    // animation
    // mMaxFrameNo == 0 <=> the Object is static
    // Nevertheless, it can change it's state and sprite in this situation
    unsigned mMaxFrameNo;
    // Do we need to switch to another
    bool mIsUpdated;
    // Provides access to graphics
    std::shared_ptr<const Model> mModel;
    // Current frame series
    const std::vector<sf::IntRect>* mFrames;
protected:
    // Current state; update is done according to it
    unsigned mState;
    // Current animation (action) frame
    unsigned mFrameNo;
    void setModel(const std::shared_ptr<const Model>& model);
public:
    Item(const std::shared_ptr<const Model>& model,
         const sf::Vector2f& position = sf::Vector2f(0,0),
         unsigned state = 0);
    ~Item();
    Item& operator = (const Item& other);
    // Returns current sprite
    // The object manages it's view itself
    void setState(unsigned state);
    void nextFrame();
};

#endif // ITEM_HPP
