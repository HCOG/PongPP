cmake_minimum_required(VERSION 3.28)
project(PongPP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL2 library information
set(SDL2_DIR "/opt/homebrew/Cellar/sdl2/2.28.5")
set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include/SDL2")
set(SDL2_LIB_DIR "${SDL2_DIR}/lib")

# SDL_image library information
set(SDL_IMAGE_DIR "/opt/homebrew/Cellar/sdl2_image/2.8.1")
set(SDL_IMAGE_INCLUDE_DIR "${SDL_IMAGE_DIR}/include/SDL2")
set(SDL_IMAGE_LIB_DIR "${SDL_IMAGE_DIR}/lib")


# SDL_ttf library information
set(SDL_TTF_DIR "/opt/homebrew/Cellar/sdl2_ttf/2.22.0")
set(SDL_TTF_INCLUDE_DIR "${SDL_TTF_DIR}/include/SDL2")
set(SDL_TTF_LIB_DIR "${SDL_TTF_DIR}/lib")

# Include directories for SDL2, SDL_image, and your project
include_directories(${SDL2_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE_DIR} ${SDL_TTF_INCLUDE_DIR} include)

# Find SDL2 and SDL2_image libraries
find_library(SDL2_LIBRARY NAME SDL2 PATHS ${SDL2_LIB_DIR} NO_DEFAULT_PATH)
find_library(SDL2_IMAGE_LIBRARY NAME SDL2_image PATHS ${SDL_IMAGE_LIB_DIR} NO_DEFAULT_PATH)

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

# Link the executable with SDL2 and SDL2_image
target_link_libraries(PongPP PRIVATE ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
