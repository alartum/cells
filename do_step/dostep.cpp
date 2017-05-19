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
RandomMoving::RandomMoving(std::shared_ptr<const ModelManager> modelManager) : mModelManager(modelManager)  {
}

void RandomMoving::operator() ( Matrix< Tile >& map, std::vector< Entity >& En ) {
    //LOG("HERE");
    cache.setSize ( map.getHeight(), map.getWidth() );
    cache.fill ( -1 );
    for ( unsigned i = 0; i < En.size(); i++ ) {
        cache.at ( En[i].getTileTo().x, En[i].getTileTo().y ) = i;
        En[i].setFuturePosition(En[i].getTileTo());
        En[i].mProperties["living_time"] += 1;
    }
    //LOG("STEP1");
    color.assign ( En.size(), 0 );

    /*LOG("CACHE");
    for (int i = 0; i < cache.getHeight(); i++) {
        for (int j = 0; j < cache.getWidth(); j++)
            std::cout << std::setw(4) << cache.at(i, j) << " ";
        std::cout << std::endl;
    }*/
    
    // Clean and multiply
   
    
    
    ///////////////////////////////////////////////////////////////////
    //                          #           m
    // mmmm    m mm   mmm    mmm#   mmm   mm#mm   mmm    m mm   mmm
    // #" "#   #"  " #"  #  #" "#  "   #    #    #" "#   #"  " #   "
    // #   #   #     #""""  #   #  m"""#    #    #   #   #      """m
    // ##m#"   #     "#mm"  "#m##  "mm"#    "mm  "#m#"   #     "mmm"
    // #
    // " ///////////////////////////////////////////////////////////// 
    
    for ( int i = 0; i < ( int ) cache.getHeight(); i++ )
        for ( int j = 0; j < ( int ) cache.getWidth(); j++ ) {
            // If grass eating entity
            int entityID = cache.at ( i, j );
            if ( entityID > -1 && color[entityID] == 0 && En[entityID].getTypeID() == OBJECT_PREDATOR_ID) {
                if (En[entityID].getTypeID() == OBJECT_PREDATOR_ID) {
                    
                    // try to eat
                    if (i > 0 && cache.at(i - 1, j) != -1 && En[cache.at(i - 1, j)].getTypeID() == OBJECT_GRASS_EATING_ID) {
                        color[cache.at(i - 1, j)] = 2; // killed
                        color[cache.at(i, j)] = 2;     // done
                        En[cache.at(i - 1, j)].setTypeID(OBJECT_CORPSE_ID );
                        En[cache.at(i - 1, j)].mProperties["living_time"] = 0;
                        //flag = true;
                    }
                    else if (j > 0 && cache.at(i, j - 1) != -1 && En[cache.at(i, j - 1)].getTypeID() == OBJECT_GRASS_EATING_ID) {
                        color[cache.at(i, j - 1)] = 2; // killed
                        color[cache.at(i, j)] = 2;     // done
                        En[cache.at(i, j - 1)].setTypeID(OBJECT_CORPSE_ID );
                        En[cache.at(i, j - 1)].mProperties["living_time"] = 0;
                        //flag = true;
                    }
                    else if (i + 1 < (int)map.getHeight() && cache.at(i + 1, j) != -1 && En[cache.at(i + 1, j)].getTypeID() == OBJECT_GRASS_EATING_ID) {
                        color[cache.at(i + 1, j)] = 2; // killed
                        color[cache.at(i, j)] = 2;     // done
                        En[cache.at(i + 1, j)].setTypeID(OBJECT_CORPSE_ID );
                        En[cache.at(i + 1, j)].mProperties["living_time"] = 0;
                        //flag = true;
                    }
                    else if (j + 1 < (int)map.getWidth() && cache.at(i, j + 1) != -1 && En[cache.at(i, j + 1)].getTypeID() == OBJECT_GRASS_EATING_ID) {
                        color[cache.at(i, j + 1)] = 2; // killed
                        color[cache.at(i, j)] = 2;     // done
                        En[cache.at(i, j + 1)].setTypeID(OBJECT_CORPSE_ID );
                        En[cache.at(i, j + 1)].mProperties["living_time"] = 0;
                        //flag = true;
                    }
                }
            }
        }
    
    
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    
    for ( int i = 0; i < ( int ) cache.getHeight(); i++ )
        for ( int j = 0; j < ( int ) cache.getWidth(); j++ ) {
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
                        switch ( rand() % (En[entityID].getTypeID() == OBJECT_PREDATOR_ID ? 4 : 7) ) {
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
                                    En[entityID].setFuturePosition(new_position);
                                    flag = true;
                                }
                        }

                        if (new_position.x >= cache.getHeight() || new_position.y >= cache.getWidth()) {
                            color[entityID] = 2;
                            En[entityID].setFuturePosition(En[entityID].getTileTo());
                            flag = true;
                            continue;
                        }
                        
                        //LOG("here");
                        if ( !flag && cache.at ( new_position.x, new_position.y ) == -1 &&
                                map.at ( new_position.x, new_position.y ).getTypeID() == TILE_GRASS_ID ) {
                            flag = true;
                            En[entityID].setFuturePosition(new_position);
                            color[entityID] = 2;
                            cache.at ( i, j ) = -1;
                            cache.at ( new_position.x, new_position.y ) = entityID;
                        } else
                            continue;
                        //LOG("end");
                }
            }
        }
    
     for (int i = 0; i < (int)En.size(); i++) {
        if (En[i].getTypeID() == OBJECT_CORPSE_ID && En[i].mProperties["living_time"] > 5) {
            if (i + 1 < (int)En.size()) {
                En[i].setTypeID( En[En.size() - 1].getTypeID());
                
                En[i].setTileTo(En[En.size() - 1].getTileTo());
                En[i].setTileFrom(En[En.size() - 1].getTileFrom());
                En[i].setFuturePosition( En[En.size() - 1].getFuturePosition() );
                //En[i].setModelManager(mModelManager);
                //En[i].loadModel();
                En[i].setState(STATE_IDLE | DIR_UP);
                En[i].initFrame();
                    
            }
            En.resize(En.size() - 1);
            i -= 1;
        }
    }//*/
    int sz = En.size();
    ///*
    for (int i = 0; i < sz; i++)  {
        
        if (En[i].getTypeID() == OBJECT_GRASS_EATING_ID && En[i].mProperties["living_time"] > 25) {
            sf::Vector2u child_position = En[i].getTileTo();
            switch( rand() % 2000 ) {
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
                if (cache.at(child_position.x, child_position.y) == -1
                    && map.at(child_position.x, child_position.y).getTypeID() == TILE_GRASS_ID
                ) {
                    //LOG("Step1");
                    cache.at(child_position.x, child_position.y) = En.size();
                    En.push_back(Entity(OBJECT_GRASS_EATING_ID, child_position, child_position, 0));
                    En[En.size() - 1].setFuturePosition( child_position );
                    En[En.size() - 1].setTileTo( child_position );
                    En[En.size() - 1].setModelManager(mModelManager);
                    En[En.size() - 1].loadModel();
                    En[En.size() - 1].setState(STATE_IDLE | DIR_UP);
                    En[En.size() - 1].initFrame();
                    
                    En[i].mProperties["living_time"] = 0;
                    
                    //LOG("Step2");
                }
            }
        }
    }
    
    //LOG("Chickens count = %ld", std::count_if(En.begin(), En.end(), 
    //                        [](Entity& arg) -> bool {return arg.getTypeID() == OBJECT_GRASS_EATING_ID;}));
    //*/
        
}


