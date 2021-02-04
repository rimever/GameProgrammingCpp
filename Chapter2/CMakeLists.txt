cmake_minimum_required(VERSION 3.17)
project(Chapter2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include_directories()

add_executable(Chapter2 main.cpp Game.cpp Game.h Ship.cpp Ship.h AnimSpriteComponent.cpp AnimSpriteComponent.h SpriteComponent.cpp SpriteComponent.h Component.cpp Component.h Actor.cpp Actor.h Math.cpp Math.h BGSpriteComponent.cpp BGSpriteComponent.h ../Chapter3/Math.h)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(Chapter2 ${SDL2_LIBRARIES})
target_link_libraries(Chapter2 ${SDL2_TTF_LIBRARIES})
target_link_libraries(Chapter2 ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(Chapter2 ${SDL2_MIXER_LIBRARIES})