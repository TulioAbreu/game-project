cmake_minimum_required (VERSION 3.7)
project (gameProject)
add_executable (gameProject 
    src/main.cpp
    src/rectangle.hpp
    src/window.hpp
    src/singleton.hpp
    src/camera.hpp
    src/entity.hpp
    src/entity.cpp
    src/vector2.hpp
    src/keyboard.hpp
    src/log.hpp
    src/entity-container.hpp
    src/entity-container.cpp
    src/script-manager.hpp
    src/script-manager.cpp
    src/script-library.hpp
    src/script-library.cpp
    src/config.hpp
    src/filepath.hpp
    src/sprite-manager.hpp
    third-party/json.hpp
    src/json.hpp
    src/prefab.hpp
    )

set_property(TARGET gameProject PROPERTY CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(gameProject sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

find_package(Lua51 REQUIRED)
include_directories(/usr/local/include ${LUA_INCLUDE_DIR})

target_link_libraries(gameProject ${LUA_LIBRARIES})
