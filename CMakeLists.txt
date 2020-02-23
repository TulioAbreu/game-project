cmake_minimum_required (VERSION 2.5)
project (gameProject)
add_executable (gameProject 
    src/main.cpp

    src/window.hpp
)

set_property(TARGET gameProject PROPERTY CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(gameProject sfml-system sfml-window sfml-graphics sfml-audio)