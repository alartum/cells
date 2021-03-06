#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "../model/model.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "../config/tile_ids.hpp"

class Item : public sf::Sprite
{
private:
    // Provides access to graphics
    std::shared_ptr<const Model> model_;

    // For faster access:
    //
    // Current frame series
    const AnimationState* animation_;
    // Max frame number. Needed as the Object doesn't necessary use all the
    // animation
    // mMaxFrameNo == 0 <=> the Object is static
    // Nevertheless, it can change it's state and sprite in this situation
    size_t frames_amount_;
    // Current animation (action) frame
    // Calculated according to mTickNo
    size_t frame_no_;
    // Not to be confused with mFrameNo
    // Actual tick that is 0 <= nTickNo < mAnimationTime
    // The mFrameNo is calculated according to it
    size_t tick_no_;
    // If the animation starts from random frame
    bool is_random_frame_;
    size_t animation_time_;
    // Current state; update is done according to it
    size_t state_;
public:
    Item(const sf::Vector2f& position = sf::Vector2f(0,0),
         size_t state = STATE_UNDEFINED_ID);
    ~Item();
    Item& operator = (const Item& other);
    void loadModel();
    void setModel(const std::shared_ptr<const Model>& model);
    std::shared_ptr<const Model> getModel() const;
    void setState(size_t state);
    size_t getState() const;
    // Sets frame equal to 'frame % maxFrameNo'
    // Always finishes without error
    void setFrame(size_t frame);
    size_t getFrame() const;
    // Next tick actually, changes the frame only if it is time to
    void nextFrame();
    // Initializes frame according to the AnimationState properties
    void initFrame();
    // Initializes state (may be rewritten to change default value)
    void initState();
};

#endif // ITEM_HPP
