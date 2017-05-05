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


#define DEBUG
#include "../debug.h"
////////////////////////////////////////////////////////////////////////////////////////////////
void DoStep::operator () ( Matrix< Tile >& map, std::vector< Entity > & M ) {

}

DoStep::DoStep() {
}

////////////////////////////////////////////////////////////////////////////////////////////////
RandomMoving::RandomMoving()  {
}

void RandomMoving::operator() ( Matrix< Tile >& map, std::vector< Entity >& En ) {
    cache.setSize ( map.getHeight(), map.getWidth() );
    cache.fill ( -1 );
    for ( unsigned i = 0; i < En.size(); i++ ) {
        cache.at ( En[i].getTileTo().x, En[i].getTileTo().y ) = i;
        En[i].mFuturePosition = sf::Vector2u ( 0, 0 );
    }
    color.assign ( En.size(), 0 );
    /*
    LOG ( "Entities:" );
    for ( auto& en: En ) {
        LOG ( "(%u, %u) : %d", en.getTileTo().x, en.getTileTo().y, en.getTypeID() );
    }*/
    for ( int i = 0; i < ( int ) cache.getHeight(); i++ )
        for ( int j = 0; j < ( int ) cache.getHeight(); j++ ) {
            
            // If entity
            int entityID = cache.at ( i, j );
            if ( entityID > -1 && color[entityID] == 0 ) {
                bool flag = false;
                for ( int iteration = 0; iteration < 10 && !flag; iteration++ ) {
                    //LOG("begin");
                    sf::Vector2u new_position ( i, j );
                    switch ( rand() % 7 ) {
                            case 0:
                                new_position.x -= 1;
                                break;
                            case 1:
                                new_position.y += 1;
                                break;
                            case 2:
                                new_position.x += 1;
                                break;
                            case 3:
                                new_position.y -= 1;
                                break;
                            default: {
                                color[entityID] = 2;
                                En[entityID].mFuturePosition = new_position;
                                flag = true;
                            }
                    }
                    
                    if (new_position.x < 0 || new_position.y < 0 || 
                        new_position.x >= cache.getHeight() || new_position.y >= cache.getHeight()) {
                        color[entityID] = 2;
                        En[entityID].mFuturePosition = En[entityID].getTileTo();
                        flag = true;
                        continue;
                    }
                    
                    //LOG("here");
                    if ( !flag && cache.at ( new_position.x, new_position.y ) == -1 &&
                            map.at ( new_position.x, new_position.y ).getTypeID() == TILE_GRASS_ID ) {
                        flag = true;
                        En[entityID].mFuturePosition = new_position;
                        color[entityID] = 2;
                        cache.at ( i, j ) = 0;
                        cache.at ( new_position.x, new_position.y ) = entityID;
                    } else
                        continue;
                    //LOG("end");
                }

            }
            
        }
}


