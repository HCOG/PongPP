cmake_minimum_required(VERSION 3.12)
project(PongPP)

set(CMAKE_CXX_STANDARD 11)

# Add your source files here
set(SOURCES 
    src/main.cpp
    src/game.cpp
    src/player.cpp
    src/ball.cpp
)

# Add your header files here
set(HEADERS 
    include/game.h
    include/player.h
    include/ball.h
)



# Link your project with third-party libraries
target_link_libraries(PongPP ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} )

# Add any additional libraries or dependencies here
# For example, if you're using SFML:
# find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# SDL_image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link any additional libraries or dependencies here
# For example, if you're using SFML:
# target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
