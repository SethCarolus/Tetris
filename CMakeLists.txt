cmake_minimum_required(VERSION 4.2.1)

project(Tetris CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)


set(SOURCES 
    ./Source/Main.cpp
    ./Source/TetrisModel.hpp
    ./Source/TetrisModel.cpp
    ./Source/TetrisView.hpp
    ./Source/TetrisView.cpp
    ./Source/TetrisController.hpp
    ./Source/TetrisController.cpp
    ./Source/Tetromino.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    raylib
)