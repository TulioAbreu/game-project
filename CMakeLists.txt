cmake_minimum_required (VERSION 3.7)
project (gameProject)
add_executable (gameProject 
    src/main.cpp
    src/rectangle.hpp
    src/window.hpp
    src/camera.hpp
    src/entity.hpp
    src/vector2.hpp
)

set_property(TARGET gameProject PROPERTY CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(gameProject ${SDL2_INCLUDE_DIRS})
target_link_libraries(gameProject ${SDL2_LIBRARIES})