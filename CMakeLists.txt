cmake_minimum_required (VERSION 3.7)
project (gameProject)
add_executable (gameProject 
    src/main.cpp
    src/rectangle.hpp
    src/window.hpp
    src/camera.hpp
    src/entity.hpp
    src/vector2.hpp
    src/keyboard.hpp
    src/log.hpp
    src/entity-container.hpp
)

set_property(TARGET gameProject PROPERTY CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(gameProject ${SDL2_INCLUDE_DIRS})
target_link_libraries(gameProject ${SDL2_LIBRARIES})

find_package(Boost COMPONENTS filesystem system date_time python37 REQUIRED)
message("Include dirs of boost: " ${Boost_INCLUDE_DIRS} )
message("Libs of boost: " ${Boost_LIBRARIES} )

find_package(PythonLibs REQUIRED)
message("Include dirs of Python: " ${PYTHON_INCLUDE_DIRS} )
message("Libs of Python: " ${PYTHON_LIBRARIES} )

include_directories(gameProject
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(gameProject
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)
