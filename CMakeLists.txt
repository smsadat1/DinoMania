cmake_minimum_required(VERSION 3.28)
project(DinoMania LANGUAGES CXX)

# Use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML dependencies
find_package(SFML 2.5 COMPONENTS
    audio
    graphics
    system
    window 
    REQUIRED
)

# Collect source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/dinomania/*.cpp
)

# Create game executable
add_executable(DinoMania ${SOURCES})


# Link SFML
target_link_libraries(DinoMania PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
