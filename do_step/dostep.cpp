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
RandomMoving::RandomMoving(std::shared_ptr<const ModelManager> modelManager) : model_manager_(modelManager)  {
}

void RandomMoving::operator() ( Matrix< Tile >& map, std::vector< Entity >& En ) {
    //LOG("HERE");
    cache_.setSize ( map.getHeight(), map.getWidth() );
    cache_.fill ( -1 );
    for ( unsigned i = 0; i < En.size(); i++ ) {
        cache_.at ( En[i].getTileTo().x, En[i].getTileTo().y ) = i;
        En[i].setFuturePosition(En[i].getTileTo());
        En[i].properties["living_time"] += 1;
    }
    //LOG("STEP1");
    color_.assign ( En.size(), 0 );

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
    
    for ( int i = 0; i < ( int ) cache_.getHeight(); i++ )
        for ( int j = 0; j < ( int ) cache_.getWidth(); j++ ) {
            // If grass eating entity
            int entityID = cache_.at ( i, j );
            if ( entityID > -1 && color_[entityID] == 0 && En[entityID].getID() == OBJECT_PREDATOR_ID) {
                if (En[entityID].getID() == OBJECT_PREDATOR_ID) {
                    
                    // try to eat
                    if (i > 0 && cache_.at(i - 1, j) != -1 && En[cache_.at(i - 1, j)].getID() == OBJECT_GRASS_EATING_ID) {
                        color_[cache_.at(i - 1, j)] = 2; // killed
                        color_[cache_.at(i, j)] = 2;     // done
                        En[cache_.at(i - 1, j)].setID(OBJECT_CORPSE_ID );
                        En[cache_.at(i - 1, j)].properties["living_time"] = 0;
                        //flag = true;
                    }
                    else if (j > 0 && cache_.at(i, j - 1) != -1 && En[cache_.at(i, j - 1)].getID() == OBJECT_GRASS_EATING_ID) {
                        color_[cache_.at(i, j - 1)] = 2; // killed
                        color_[cache_.at(i, j)] = 2;     // done
                        En[cache_.at(i, j - 1)].setID(OBJECT_CORPSE_ID );
                        En[cache_.at(i, j - 1)].properties["living_time"] = 0;
                        //flag = true;
                    }
                    else if (i + 1 < (int)map.getHeight() && cache_.at(i + 1, j) != -1 && En[cache_.at(i + 1, j)].getID() == OBJECT_GRASS_EATING_ID) {
                        color_[cache_.at(i + 1, j)] = 2; // killed
                        color_[cache_.at(i, j)] = 2;     // done
                        En[cache_.at(i + 1, j)].setID(OBJECT_CORPSE_ID );
                        En[cache_.at(i + 1, j)].properties["living_time"] = 0;
                        //flag = true;
                    }
                    else if (j + 1 < (int)map.getWidth() && cache_.at(i, j + 1) != -1 && En[cache_.at(i, j + 1)].getID() == OBJECT_GRASS_EATING_ID) {
                        color_[cache_.at(i, j + 1)] = 2; // killed
                        color_[cache_.at(i, j)] = 2;     // done
                        En[cache_.at(i, j + 1)].setID(OBJECT_CORPSE_ID );
                        En[cache_.at(i, j + 1)].properties["living_time"] = 0;
                        //flag = true;
                    }
                }
            }
        }
    
    
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    
    for ( int i = 0; i < ( int ) cache_.getHeight(); i++ )
        for ( int j = 0; j < ( int ) cache_.getWidth(); j++ ) {
            // If grass eating entity
            int entityID = cache_.at ( i, j );
            if ( entityID > -1 && color_[entityID] == 0 && 
                            (En[entityID].getID() == OBJECT_GRASS_EATING_ID ||
                            En[entityID].getID() == OBJECT_PREDATOR_ID ))
            {
                bool flag = false;
            
                    for ( int iteration = 0; iteration < 10 && !flag; iteration++ ) {
                        //LOG("begin");
                        sf::Vector2u new_position ( i, j );
                        switch ( rand() % (En[entityID].getID() == OBJECT_PREDATOR_ID ? 4 : 7) ) {
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
                                    color_[entityID] = 2;
                                    En[entityID].setFuturePosition(new_position);
                                    flag = true;
                                }
                        }

                        if (new_position.x >= cache_.getHeight() || new_position.y >= cache_.getWidth()) {
                            color_[entityID] = 2;
                            En[entityID].setFuturePosition(En[entityID].getTileTo());
                            flag = true;
                            continue;
                        }
                        
                        //LOG("here");
                        if ( !flag && cache_.at ( new_position.x, new_position.y ) == -1 &&
                                map.at ( new_position.x, new_position.y ).getID() == TILE_GRASS_ID ) {
                            flag = true;
                            En[entityID].setFuturePosition(new_position);
                            color_[entityID] = 2;
                            cache_.at ( i, j ) = -1;
                            cache_.at ( new_position.x, new_position.y ) = entityID;
                        } else
                            continue;
                        //LOG("end");
                }
            }
        }
    
     for (int i = 0; i < (int)En.size(); i++) {
        if (En[i].getID() == OBJECT_CORPSE_ID && En[i].properties["living_time"] > 5) {
            if (i + 1 < (int)En.size()) {
                En[i].setID( En[En.size() - 1].getID());
                
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
        
        if (En[i].getID() == OBJECT_GRASS_EATING_ID && En[i].properties["living_time"] > 25) {
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
                if (cache_.at(child_position.x, child_position.y) == -1
                    && map.at(child_position.x, child_position.y).getID() == TILE_GRASS_ID
                ) {
                    //LOG("Step1");
                    cache_.at(child_position.x, child_position.y) = En.size();
                    En.push_back(Entity(OBJECT_GRASS_EATING_ID, child_position, child_position, 0));
                    En[En.size() - 1].setFuturePosition( child_position );
                    En[En.size() - 1].setTileTo( child_position );
                    En[En.size() - 1].setModelManager(model_manager_);
                    En[En.size() - 1].loadModel();
                    En[En.size() - 1].setState(STATE_IDLE | DIR_UP);
                    En[En.size() - 1].initFrame();
                    
                    En[i].properties["living_time"] = 0;
                    
                    //LOG("Step2");
                }
            }
        }
    }
    
    //LOG("Chickens count = %ld", std::count_if(En.begin(), En.end(), 
    //                        [](Entity& arg) -> bool {return arg.getID() == OBJECT_GRASS_EATING_ID;}));
    //*/
        
}


