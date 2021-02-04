cmake_minimum_required(VERSION 3.17)
project(Chapter3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Chapter3 main.cpp Math.cpp Math.h Actor.cpp Actor.h Component.cpp Component.h SpriteComponent.cpp SpriteComponent.h Ship.cpp Ship.h Game.cpp Game.h Asteroid.cpp Asteroid.h CircleComponent.cpp CircleComponent.h MoveComponent.cpp MoveComponent.h InputComponent.cpp InputComponent.h Random.cpp Random.h Laser.cpp Laser.h)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(Chapter3 ${SDL2_LIBRARIES})
target_link_libraries(Chapter3 ${SDL2_TTF_LIBRARIES})
target_link_libraries(Chapter3 ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(Chapter3 ${SDL2_MIXER_LIBRARIES})