#include "model.hpp"
#define DEBUG
#include "../debug.h"
#include <iostream>
#include "../config/tile_ids.hpp"

Model::Model(const std::shared_ptr<const sf::Texture>& texture) :
    texture_(texture)
{
    bad_state_.setName("undefined");
}

const AnimationState& Model::getAnimation(int state_id) const{
    try{
        return animations_.at(state_id);
    }
    catch (const std::out_of_range& oor){
        //PERROR("No animation for state 0x%x", state_id);
        try{
            return animations_.at(0);
        }
        catch(...){
            return bad_state_;
        }
    }
}

void Model::loadAnimation(int state_id, const AnimationState& animation_state){
    animations_[state_id] = animation_state;
}

const std::shared_ptr<const sf::Texture> &Model::getTexture() const
{
    return texture_;
}

void Model::setTexture(const std::shared_ptr<const sf::Texture>& texture)
{
    texture_ = texture;
}

void Model::setName(const std::string& name){
    name_ = name;
}

const std::string& Model::getName() const{
    return name_;
}
