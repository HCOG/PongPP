cmake_minimum_required(VERSION 3.12)
project(PongPP)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL2 library information
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Include directories for SDL2 and SDL_image
include_directories(PongPP PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} include)

# Library directories for SDL2 and SDL_image
link_directories(PongPP PRIVATE ${SDL2_LIBDIR} ${SDL2_IMAGE_LIBDIR})

# Add your source files here
set(SOURCES 
    src/Actor.cpp
    src/AnimSpriteComponent.cpp
    src/Ball.cpp
    src/BGSpriteComponent.cpp
    src/Component.cpp
    src/Main.cpp
    src/Math.cpp
    src/Game.cpp
    src/SpriteComponent.cpp
)

# Add an executable target
add_executable(PongPP ${SOURCES})

# Link the executable with SDL2 and SDL_image
target_link_libraries(PongPP PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
