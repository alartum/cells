#ifndef MODEL_HPP
#define MODEL_HPP

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include "../animation_state/animationstate.hpp"
#include <map>

// Indexing in vectors is done accroding to defines! //
class Model
{
    // Not everyone is allowed to change model's properties
    friend class ModelManager;
public:
    Model(const std::shared_ptr<const sf::Texture>& texture);
    void setTexture(const std::shared_ptr<const sf::Texture>& texture);
    const std::shared_ptr<const sf::Texture>& getTexture() const;
    const AnimationState& getAnimation(int state_id) const;
    void loadAnimation(int state_id, const AnimationState& animation_state);
    void setName(const std::string& name);
    const std::string& getName() const;
private:
    std::string name_;
    // Multiple entries for one texture are unwanted
    std::shared_ptr<const sf::Texture> texture_;
    std::map<int, AnimationState> animations_;
    AnimationState bad_state_;
};

#endif // MODEL_HPP
