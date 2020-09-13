cmake_minimum_required (VERSION 3.7)
project (gameProject)
add_executable (gameProject 
    src/sprite-manager.hpp
    src/scene.hpp
    src/graphics/camera/camera.hpp src/graphics/camera/camera.cpp
    src/json.cpp
    src/sprite-manager.cpp
    src/json.hpp
    src/config.hpp
    src/script-manager.hpp
    src/scene.cpp
    src/entities/container/container.hpp src/entities/container/container.cpp
    src/script-library.cpp
    src/entity.hpp
    src/singleton.hpp
    src/console.hpp
    src/main.cpp
    src/graphics/window/window.hpp
    src/keyboard.hpp
    src/utils/filepath/filepath.hpp src/utils/filepath/filepath.cpp
    src/entities/prefab/prefab.hpp src/entities/prefab/prefab.cpp
    src/utils/log/log.hpp
    src/entity.cpp
    src/script-library.hpp
    src/rectangle.hpp
    src/script-manager.cpp
    src/graphics/window/window.cpp
    src/utils/vector2/vector2.hpp
    third-party/imgui_demo.cpp
    third-party/imgui.h
    third-party/imgui-SFML.h
    third-party/imgui-SFML_export.h
    third-party/imgui_widgets.cpp
    third-party/json.hpp
    third-party/imgui_internal.h
    third-party/imgui-SFML.cpp
    third-party/imconfig.h
    third-party/imstb_truetype.h
    third-party/imstb_rectpack.h
    third-party/imstb_textedit.h
    third-party/imconfig-SFML.h
    third-party/imgui_draw.cpp
    third-party/imgui.cpp)

set_property(TARGET gameProject PROPERTY CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(gameProject sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

find_package(Lua51 REQUIRED)
include_directories(/usr/local/include ${LUA_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(gameProject ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )


target_link_libraries(gameProject ${LUA_LIBRARIES})
add_compile_definitions(DEBUG)