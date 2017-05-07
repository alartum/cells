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
        //En[i].mFuturePosition = sf::Vector2u ( 0, 0 );
    }
    color.assign ( En.size(), 0 );
    /*
    LOG ( "Entities:" );
    for ( auto& en: En ) {
        LOG ( "(%u, %u) : %d", en.getTileTo().x, en.getTileTo().y, en.getTypeID() );
    }*/
    
    ///////////////////////////////////////////////////////////////////
    //                          #           m
    // mmmm    m mm   mmm    mmm#   mmm   mm#mm   mmm    m mm   mmm
    // #" "#   #"  " #"  #  #" "#  "   #    #    #" "#   #"  " #   "
    // #   #   #     #""""  #   #  m"""#    #    #   #   #      """m
    // ##m#"   #     "#mm"  "#m##  "mm"#    "mm  "#m#"   #     "mmm"
    // #
    // " ///////////////////////////////////////////////////////////// 
    
    for ( int i = 0; i < ( int ) cache.getHeight(); i++ )
        for ( int j = 0; j < ( int ) cache.getHeight(); j++ ) {
            // If grass eating entity
            int entityID = cache.at ( i, j );
            if ( entityID > -1 && color[entityID] == 0 && En[entityID].getTypeID() == OBJECT_PREDATOR_ID) {
                if (En[entityID].getTypeID() == OBJECT_PREDATOR_ID) {
                    
                    // try to eat
                    if (i > 0 && cache.at(i - 1, j) != -1 && En[cache.at(i - 1, j)].getTypeID() == OBJECT_GRASS_EATING_ID) {
                        color[cache.at(i - 1, j)] = 2; // killed
                        color[cache.at(i, j)] = 2;     // done
                        En[cache.at(i - 1, j)].setTypeID(OBJECT_CORPSE_ID );
                        //flag = true;
                    }
                    else if (j > 0 && cache.at(i, j - 1) != -1 && En[cache.at(i, j - 1)].getTypeID() == OBJECT_GRASS_EATING_ID) {
                        color[cache.at(i, j - 1)] = 2; // killed
                        color[cache.at(i, j)] = 2;     // done
                        En[cache.at(i, j - 1)].setTypeID(OBJECT_CORPSE_ID );
                        //flag = true;
                    }
                    else if (i + 1 < (int)map.getHeight() && cache.at(i + 1, j) != -1 && En[cache.at(i + 1, j)].getTypeID() == OBJECT_GRASS_EATING_ID) {
                        color[cache.at(i + 1, j)] = 2; // killed
                        color[cache.at(i, j)] = 2;     // done
                        En[cache.at(i + 1, j)].setTypeID(OBJECT_CORPSE_ID );
                        //flag = true;
                    }
                    else if (j + 1 < (int)map.getWidth() && cache.at(i, j + 1) != -1 && En[cache.at(i, j + 1)].getTypeID() == OBJECT_GRASS_EATING_ID) {
                        color[cache.at(i, j + 1)] = 2; // killed
                        color[cache.at(i, j)] = 2;     // done
                        En[cache.at(i, j + 1)].setTypeID(OBJECT_CORPSE_ID );
                        //flag = true;
                    }
                }
            }
        }
    
    
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    
    
    
    for ( int i = 0; i < ( int ) cache.getHeight(); i++ )
        for ( int j = 0; j < ( int ) cache.getHeight(); j++ ) {
            // If grass eating entity
            int entityID = cache.at ( i, j );
            if ( entityID > -1 && color[entityID] == 0 && 
                            (En[entityID].getTypeID() == OBJECT_GRASS_EATING_ID || 
                            En[entityID].getTypeID() == OBJECT_PREDATOR_ID )) 
            {
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
                            cache.at ( i, j ) = -1;
                            cache.at ( new_position.x, new_position.y ) = entityID;
                        } else
                            continue;
                        //LOG("end");
                }
            }
        }
}


