cmake_minimum_required(VERSION 3.8)
project(PongPP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL2 library information
find_package(SDL2 QUIET)
find_package(SDL2_image QUIET)
find_package(SDL2_ttf QUIET)

include(FetchContent)

if(NOT SDL2_FOUND)
    message(STATUS "SDL2 not found, fetching it from GitHub ... ")
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY http://gitHub.com//libsdl-org/SDL.git
        GIT_TAG release-2.30.7
    )
    FetchContent_MakeAvailable(SDL2)
endif()

if(NOT TARGET SDL2_image::SDL2_image)
    message(STATUS "SDL2_image not found, fetching it from GitHub ... ")
    FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.8.2
    )
    FetchContent_MakeAvailable(SDL2_image)
endif()

if(NOT TARGET SDL2_ttf::SDL2_ttf)
    message(STATUS "SDL2_ttf not found, fetching it from GitHub ... ")
    FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.22.0
    )
    FetchContent_MakeAvailable(SDL2_ttf)
endif()

# Include directories for SDL2, SDL_image, and your project
include_directories(include)

# Add your source files here
set(SOURCES 
    src/Actor.cpp
    src/AnimSpriteComponent.cpp
    src/Ball.cpp
    src/BGSpriteComponent.cpp
    src/Component.cpp
    src/Main.cpp
    src/Cust_Math.cpp
    src/Game.cpp
    src/Paddle.cpp
    src/SpriteComponent.cpp
    src/PaddleSpriteComponent.cpp
)

# Add an executable target
add_executable(PongPP ${SOURCES})

target_link_libraries(PongPP SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)

# Copy SDL2.dll or SDL2d.dll to the output directory after build
add_custom_command(TARGET PongPP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:SDL2::SDL2>/SDL2$<$<CONFIG:Debug>:d>.dll"
        $<TARGET_FILE_DIR:PongPP>)

# Copy SDL2_image.dll or SDL2_imaged.dll to the output directory after build
add_custom_command(TARGET PongPP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:SDL2_image::SDL2_image>/SDL2_image$<$<CONFIG:Debug>:d>.dll"
        $<TARGET_FILE_DIR:PongPP>)

# Copy SDL2_ttf.dll or SDL2_ttfd.dll to the output directory after build
add_custom_command(TARGET PongPP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:SDL2_ttf::SDL2_ttf>/SDL2_ttf$<$<CONFIG:Debug>:d>.dll"
        $<TARGET_FILE_DIR:PongPP>)