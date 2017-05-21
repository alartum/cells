#include "dostep.hpp"
#include <functional>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>


#define DEBUG
#include "../debug.h"
////////////////////////////////////////////////////////////////////////////////////////////////
void DoStep::operator () ( Matrix< Tile >& map, std::vector< Entity > & M ) {

}

DoStep::DoStep() {
}

////////////////////////////////////////////////////////////////////////////////////////////////
RandomMoving::RandomMoving(std::shared_ptr<const ModelManager> modelManager) : model_manager_(modelManager)  {
}

#define COLOR_WAIT 0
#define COLOR_ACTIVE 1
#define COLOR_FINISHED 2

void RandomMoving::initializationStage ( Matrix< Tile >& map, std::vector< Entity >& En ) {
    cache_.setSize ( map.getHeight(), map.getWidth() );
    cache_.fill ( -1 );
    for ( unsigned i = 0; i < En.size(); i++ ) {
        cache_.at ( En[i].getTileTo().x, En[i].getTileTo().y ) = i;
        En[i].setFuturePosition(En[i].getTileTo());
        En[i].properties["living_time"] += 1;
    }
    color_.assign ( En.size(), COLOR_WAIT );
}

void RandomMoving::huntingStage ( Matrix< Tile >& map, std::vector< Entity >& En ) {
    for (int i = 0; i < ( int ) cache_.getHeight(); i++)
        for (int j = 0; j < ( int ) cache_.getWidth(); j++) {
            
            int currentEntityId = cache_.at ( i, j );
            
            if (currentEntityId == -1)
                continue;
            
            #define TRY_TO_EAT(x, y, flag) \
                if ( (x) >= 0 && (y) >= 0 && (x) < ( int ) cache_.getHeight() && (y) < ( int ) cache_.getWidth() ) {        \
                    int victimId = cache_.at ((x), (y));                                                \
                    if ( victimId != -1 && En[victimId].getID() == OBJECT_GRASS_EATING_ID ) {           \
                        color_[cache_.at((x), (y))] = 2;                        /* killed */            \
                        color_[cache_.at((x), (y))] = 2;                        /* done */              \
                        En[cache_.at((x), (y))].setID(OBJECT_CORPSE_ID );       /* corpse created */    \
                        En[cache_.at((x), (y))].properties["living_time"] = 0;                          \
                        flag = true;                                                                    \
                    }                                                                                   \
                }
            //*/
            
            if (En[currentEntityId].getID() == OBJECT_PREDATOR_ID && color_[currentEntityId] == COLOR_WAIT) {
                bool flag = false;
                if (flag == false) {
                    TRY_TO_EAT(i - 1, j, flag); 
                }
                if (flag == false) {
                    TRY_TO_EAT(i + 1, j, flag); 
                }
                if (flag == false) {
                    TRY_TO_EAT(i, j - 1, flag); 
                }
                if (flag == false) {
                    TRY_TO_EAT(i, j + 1, flag); 
                }
            }
            #undef TRY_TO_EAT
        }
}

void RandomMoving::grassEatingMovingStage ( Matrix< Tile >& map, std::vector< Entity >& En ) {
    for ( int i = 0; i < ( int ) cache_.getHeight(); i++ )
        for ( int j = 0; j < ( int ) cache_.getWidth(); j++ ) {
            int currentEntityId = cache_.at ( i, j );
            if (currentEntityId != -1 && color_[currentEntityId] == COLOR_WAIT && En[currentEntityId].getID() == OBJECT_GRASS_EATING_ID) {
               
                bool flag = false;
                sf::Vector2f force;
                for ( int i0 = -2; i0 <= 2; i0++ )
                    for ( int j0 = -2; j0 <= 2; j0++ ) {
                        if (i + i0 >= 0 && i + i0 < ( int ) cache_.getHeight() && j + j0 >= 0 && j + j0 < ( int ) cache_.getWidth()) {
                            int aimId = cache_.at( i + i0, j + j0 );
                            if ( aimId == -1 ) 
                                continue;
                            if ( En[aimId].getID() != OBJECT_PREDATOR_ID )
                                continue;
                            
                            int dist = i0 * i0 + j0 * j0;                            
                           
                            force.x -= ( double ) i0 / dist;
                            force.y -= ( double ) j0 / dist;
                        }
                    }
                
                #define TRY_TO_MOVE(new_position, flag) \
                if (new_position.x >= 0 && new_position.x < cache_.getHeight() && \
                    new_position.y >= 0 && new_position.y < cache_.getWidth()) \
                    if ( cache_.at ( new_position.x, new_position.y ) == -1 &&                         \
                                map.at ( new_position.x, new_position.y ).getID() == TILE_GRASS_ID ) {          \
                            flag = true;                                                                        \
                            En[currentEntityId].setFuturePosition(new_position);                                \
                            color_[currentEntityId] = 2;                                                        \
                            cache_.at ( i, j ) = -1;                                                            \
                            cache_.at ( new_position.x, new_position.y ) = currentEntityId;                     \
                        }
                //if (force.x != 0 || force.y != 0)
                //    LOG("(%d, %d) -> FORCE = (%.5f, %.5f)", i, j, force.x, force.y);
                
                if (force.x != 0 || force.y != 0) {
                    if (!flag && abs(force.x) >= abs(force.y)) {
                        if (!flag && force.x > 0) {
                            sf::Vector2u new_position ( i + 1, j );
                            TRY_TO_MOVE(new_position, flag);
                        }
                        if (!flag && force.x < 0) {
                            sf::Vector2u new_position ( i - 1, j );
                            TRY_TO_MOVE(new_position, flag);
                        }
                    }
                    if (!flag && abs(force.x) <= abs(force.y)) {
                        if (!flag && force.y > 0) {
                            sf::Vector2u new_position ( i, j + 1 );
                            TRY_TO_MOVE(new_position, flag);
                        }
                        if (!flag && force.y < 0) {
                            sf::Vector2u new_position ( i , j - 1 );
                            TRY_TO_MOVE(new_position, flag);
                        }
                    }    
                }
                #undef TRY_TO_MOVE
                
                if (flag)
                    continue;
                
                
                // RandomMoving
                for ( int iteration = 0; iteration < 5 && !flag; iteration++ ) {
                    sf::Vector2u new_position ( i, j );
                    switch ( rand() % 7 ) { // 7 is magic constant
                        case 0: new_position.x -= 1; break;
                        case 1: new_position.y += 1; break;
                        case 2: new_position.x += 1; break;
                        case 3: new_position.y -= 1; break;
                        default: {
                            color_[currentEntityId] = 2;
                            En[currentEntityId].setFuturePosition(new_position);
                            flag = true;
                        }
                    }

                    if (new_position.x >= cache_.getHeight() || new_position.y >= cache_.getWidth()) {
                        color_[currentEntityId] = 2;
                        En[currentEntityId].setFuturePosition(En[currentEntityId].getTileTo());
                        flag = true;
                        continue;
                    }
                        
                        if ( !flag && cache_.at ( new_position.x, new_position.y ) == -1 &&
                                map.at ( new_position.x, new_position.y ).getID() == TILE_GRASS_ID ) {
                            flag = true;
                            En[currentEntityId].setFuturePosition(new_position);
                            color_[currentEntityId] = 2;
                            cache_.at ( i, j ) = -1;
                            cache_.at ( new_position.x, new_position.y ) = currentEntityId;
                        } else
                            continue;
                }
            }
                
        }
}

void RandomMoving::predatorsMovingStage ( Matrix< Tile >& map, std::vector< Entity >& En ) {
    for ( int i = 0; i < ( int ) cache_.getHeight(); i++ )
        for ( int j = 0; j < ( int ) cache_.getWidth(); j++ ) {
            int currentEntityId = cache_.at ( i, j );
            if (currentEntityId != -1 && color_[currentEntityId] == COLOR_WAIT && En[currentEntityId].getID() == OBJECT_PREDATOR_ID) {
               
                bool flag = false;
                sf::Vector2f force;
                for ( int i0 = -2; i0 <= 2; i0++ )
                    for ( int j0 = -2; j0 <= 2; j0++ ) {
                        if (i + i0 >= 0 && i + i0 < ( int ) cache_.getHeight() && j + j0 >= 0 && j + j0 < ( int ) cache_.getWidth()) {
                            int aimId = cache_.at( i + i0, j + j0 );
                            if ( aimId == -1 ) 
                                continue;
                            if ( En[aimId].getID() != OBJECT_GRASS_EATING_ID)
                                continue;
                            
                            int dist = i0 * i0 + j0 * j0;                            
                           
                            force.x += ( double ) i0 / dist;
                            force.y += ( double ) j0 / dist;
                        }
                    }
                
                #define TRY_TO_MOVE(new_position, flag) \
                if (new_position.x >= 0 && new_position.x < cache_.getHeight() && \
                    new_position.y >= 0 && new_position.y < cache_.getWidth()) \
                    if ( cache_.at ( new_position.x, new_position.y ) == -1 &&                         \
                                map.at ( new_position.x, new_position.y ).getID() == TILE_GRASS_ID ) {          \
                            flag = true;                                                                        \
                            En[currentEntityId].setFuturePosition(new_position);                                \
                            color_[currentEntityId] = 2;                                                        \
                            cache_.at ( i, j ) = -1;                                                            \
                            cache_.at ( new_position.x, new_position.y ) = currentEntityId;                     \
                        }
                //if (force.x != 0 || force.y != 0)
                //    LOG("(%d, %d) -> FORCE = (%.5f, %.5f)", i, j, force.x, force.y);
                
                if (force.x != 0 || force.y != 0) {
                    if (!flag && abs(force.x) >= abs(force.y)) {
                        if (!flag && force.x > 0) {
                            sf::Vector2u new_position ( i + 1, j );
                            TRY_TO_MOVE(new_position, flag);
                        }
                        if (!flag && force.x < 0) {
                            sf::Vector2u new_position ( i - 1, j );
                            TRY_TO_MOVE(new_position, flag);
                        }
                    }
                    if (!flag && abs(force.x) <= abs(force.y)) {
                        if (!flag && force.y > 0) {
                            sf::Vector2u new_position ( i, j + 1 );
                            TRY_TO_MOVE(new_position, flag);
                        }
                        if (!flag && force.y < 0) {
                            sf::Vector2u new_position ( i , j - 1 );
                            TRY_TO_MOVE(new_position, flag);
                        }
                    }    
                }
                #undef TRY_TO_MOVE
                
                if (flag)
                    continue;
                
                
                // RandomMoving
                for ( int iteration = 0; iteration < 5 && !flag; iteration++ ) {
                    sf::Vector2u new_position ( i, j );
                    switch ( rand() % 7 ) { // 7 is magic constant
                        case 0: new_position.x -= 1; break;
                        case 1: new_position.y += 1; break;
                        case 2: new_position.x += 1; break;
                        case 3: new_position.y -= 1; break;
                        default: {
                            color_[currentEntityId] = 2;
                            En[currentEntityId].setFuturePosition(new_position);
                            flag = true;
                        }
                    }

                    if (new_position.x >= cache_.getHeight() || new_position.y >= cache_.getWidth()) {
                        color_[currentEntityId] = 2;
                        En[currentEntityId].setFuturePosition(En[currentEntityId].getTileTo());
                        flag = true;
                        continue;
                    }
                        
                        if ( !flag && cache_.at ( new_position.x, new_position.y ) == -1 &&
                                map.at ( new_position.x, new_position.y ).getID() == TILE_GRASS_ID ) {
                            flag = true;
                            En[currentEntityId].setFuturePosition(new_position);
                            color_[currentEntityId] = 2;
                            cache_.at ( i, j ) = -1;
                            cache_.at ( new_position.x, new_position.y ) = currentEntityId;
                        } else
                            continue;
                }
            }
                
        }
}

void RandomMoving::deleteCorpses ( Matrix< Tile >& map, std::vector< Entity >& En ) {
    for (int i = 0; i < (int)En.size(); i++) {
        if (En[i].getID() == OBJECT_CORPSE_ID && En[i].properties["living_time"] > 3) {
            if (i + 1 < (int)En.size()) {
                En[i].setID( En[En.size() - 1].getID());
                En[i].setTileTo(En[En.size() - 1].getTileTo());
                En[i].setTileFrom(En[En.size() - 1].getTileFrom());
                En[i].setFuturePosition( En[En.size() - 1].getFuturePosition() );
                En[i].setState(STATE_IDLE | DIR_UP);
                En[i].initFrame();
                    
            }
            En.resize(En.size() - 1);
            i -= 1;
        }
    }
}

void RandomMoving::multiplicationStage ( Matrix< Tile >& map, std::vector< Entity >& En ) {
    int sz = En.size();
    
    for (int i = 0; i < sz; i++)  {
        if (En[i].getID() == OBJECT_GRASS_EATING_ID && En[i].properties["living_time"] > 25) {
            sf::Vector2u child_position = En[i].getTileTo();
            switch( rand() % 3000 ) {
                case 0:
                    child_position.x += 1;
                    break;
                case 1:
                    child_position.x -= 1;
                    break;
                case 2:
                    child_position.y -= 1;
                    break;
                case 3:
                    child_position.y += 1;
                    break;
            }
            if (child_position.x < 0 || child_position.x >= map.getHeight() ||
                child_position.y < 0 || child_position.y >= map.getWidth()
                ) {
                ;
            }
            else {
                if (cache_.at(child_position.x, child_position.y) == -1
                    && map.at(child_position.x, child_position.y).getID() == TILE_GRASS_ID
                ) {
                    cache_.at(child_position.x, child_position.y) = En.size();
                    En.push_back(Entity(OBJECT_GRASS_EATING_ID, child_position, child_position, 0));
                    En[En.size() - 1].setFuturePosition( child_position );
                    En[En.size() - 1].setTileTo( child_position );
                    En[En.size() - 1].setModelManager(model_manager_);
                    En[En.size() - 1].loadModel();
                    En[En.size() - 1].setState(STATE_IDLE | DIR_UP);
                    En[En.size() - 1].initFrame();
                    
                    En[i].properties["living_time"] = 0;
                }
            }
        }
    }
}


void RandomMoving::operator() ( Matrix< Tile >& map, std::vector< Entity >& En ) {
    initializationStage(map, En);
    huntingStage( map, En );
    grassEatingMovingStage( map, En );
    predatorsMovingStage( map, En );\
    deleteCorpses( map, En );
    multiplicationStage( map, En );
}


