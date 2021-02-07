cmake_minimum_required(VERSION 3.17)
project(Chapter4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Chapter4 main.cpp cmake-build-debug/AIState.cpp cmake-build-debug/AIState.h Component.cpp Component.h Actor.cpp Actor.h Math.cpp Math.h CircleComponent.cpp CircleComponent.h Bullet.cpp Bullet.h SpriteComponent.cpp SpriteComponent.h MoveComponent.cpp MoveComponent.h NavComponent.cpp NavComponent.h Tile.cpp Tile.h Search.cpp Game.cpp Game.h Grid.cpp Grid.h Tower.cpp Tower.h Enemy.cpp Enemy.h AIComponent.cpp AIComponent.h AIState.cpp AIState.h)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(Chapter4 ${SDL2_LIBRARIES})
target_link_libraries(Chapter4 ${SDL2_TTF_LIBRARIES})
target_link_libraries(Chapter4 ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(Chapter4 ${SDL2_MIXER_LIBRARIES})