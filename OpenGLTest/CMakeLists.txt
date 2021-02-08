cmake_minimum_required(VERSION 3.12)
project(OpenGLTest)

set(CMAKE_CXX_STANDARD 14)

# TODO:格納されているバージョンに合わせてパスを修正する
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.2/include/GLFW)

set(GLAD_H /usr/local/include/glad)
set(KH_H /usr/local/include/KHR)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H})

# Add target link
# TODO:格納されているバージョンに合わせてパスを修正する
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.2/lib/libglfw.3.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

# Execute compile command
# This glad.c said in step 2 that it should be pulled into the project. Pay attention to the path
set(SOURCE_FILES "src/glad.c" "main.cpp")
add_executable(OpenGLTest ${SOURCE_FILES})

# mac, it's important to take this step
if (APPLE)
    target_link_libraries(OpenGLTest "-framework OpenGL")
    target_link_libraries(OpenGLTest "-framework GLUT")
endif()