cmake_minimum_required(VERSION 3.28)
project(DinoMania LANGUAGES CXX)

# Use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    message(STATUS "Building for Windows")
elseif(UNIX)
    message(STATUS "Building for Linux (Unix)")
endif

if(WIN32)
    add_definitions(-DSFML_STATIC)          # for static SFML on Windows
    set(SFML_DIR "C:/SFML/lib/cmake/SFML")  # assuming installed
endif()

# Find SFML dependencies (Linux)
find_package(SFML 2.5 COMPONENTS
    audio
    graphics
    system
    window 
    REQUIRED
)

# Collect source files
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
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
