set(CMAKE_C_COMPILER "/usr/bin/gcc-6")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-6")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -fopenmp -pthread -g")

set(SRC_FILES test_algo.cpp field/field.cpp object/object.cpp do_step/dostep.cpp tile/tile.cpp generate_map/generatemap.cpp generate_objects/generateobjects.cpp main.cpp model/model.cpp  item/item.cpp model_manager/modelmanager.cpp game_item/gameitem.cpp entity/entity.cpp)

add_executable(cells ${SRC_FILES})
target_link_libraries(cells sfml-window sfml-graphics sfml-system gomp X11 pthread)
# install(TARGETS cells_kdevelop RUNTIME DESTINATION bin)
