cmake_minimum_required (VERSION 3.7)
project (gameProject)

file (GLOB_RECURSE gameProjectSrc
    "src/*.hpp"
    "src/*.cpp"
)
file (GLOB thirdPartySrc
    "third-party/*.hpp"
    "third-party/*.cpp"
)

add_executable (gameProject
    ${gameProjectSrc}
    ${thirdPartySrc}
)

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