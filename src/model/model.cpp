#include "model.hpp"
#define DEBUG
#include "debug.h"
#include <iostream>
#include "tileinfo/tile_ids.hpp"

Model::Model(const std::shared_ptr<const sf::Texture>& texture) :
    mTexture(texture)
{
    mBadState.setName("undefined");
}

const AnimationState& Model::getAnimation(int state_id) const{
    VAR_LOG(state_id);
    try{
        return mAnimations.at(state_id);
    }
    catch (const std::out_of_range& oor){
        PERROR("No animation for state =  0x%x", state_id);
        return mBadState;
    }
}

void Model::loadAnimation(int state_id, const AnimationState& animation_state){
    mAnimations[state_id] = animation_state;
}

const std::shared_ptr<const sf::Texture> &Model::getTexture() const
{
    return mTexture;
}

void Model::setTexture(const std::shared_ptr<const sf::Texture>& texture)
{
    mTexture = texture;
}

void Model::setName(const std::string& name){
    mName = name;
}

const std::string& Model::getName() const{
    return mName;
}
