set(CMAKE_C_COMPILER "/usr/bin/gcc-6")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-6")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wpedantic -fopenmp -pthread")

set(SRC_FILES test.cpp field/field.cpp generator/generator.cpp step_algorithm/step_algorithm.cpp object/object.cpp)
project(cells_kdevelop)

add_executable(cells_kdevelop ${SRC_FILES})
target_link_libraries(cells_kdevelop sfml-window sfml-graphics sfml-system gomp X11 pthread)
# install(TARGETS cells_kdevelop RUNTIME DESTINATION bin)
