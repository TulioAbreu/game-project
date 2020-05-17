cmake_minimum_required (VERSION 3.7)
project (gameProject)
add_executable (gameProject 
    src/sprite-manager.hpp
    src/sprite-manager.cpp
    src/scene.hpp
    src/camera.hpp
    src/json.hpp
    src/config.hpp
    src/script-manager.hpp
    src/scene.cpp
    src/entity-container.hpp
    src/script-library.cpp
    src/entity.hpp
    src/singleton.hpp
    src/main.cpp
    src/entity-container.cpp
    src/window.hpp
    src/keyboard.hpp
    src/filepath.hpp
    src/prefab.hpp
    src/log.hpp
    src/entity.cpp
    src/script-library.hpp
    src/filepath.cpp
    src/rectangle.hpp
    src/script-manager.cpp
    src/window.cpp
    src/vector2.hpp

    third-party/json.hpp
    )

set_property(TARGET gameProject PROPERTY CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(gameProject sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

find_package(Lua51 REQUIRED)
include_directories(/usr/local/include ${LUA_INCLUDE_DIR})

target_link_libraries(gameProject ${LUA_LIBRARIES})
