cmake_minimum_required(VERSION 3.14)
project(RaylibGame LANGUAGES CXX C)

# 1. Include the FetchContent module
include(FetchContent)

# 2. Turn off raylib configuration options to speed up building
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(BUILD_GAMES OFF CACHE INTERNAL "")

# 3. Declare the raylib repository and specific version tag
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        master
)

# 4. Make raylib available to the project
FetchContent_MakeAvailable(raylib)

# 5. Define your game's executable name and source files
# Removed the '$' symbols so "Tactics" is treated as the actual target name
add_executable(Tactics main.cpp)

# 6. Link raylib to your executable target
target_link_libraries(Tactics PRIVATE raylib)
