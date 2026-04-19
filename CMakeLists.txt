cmake_minimum_required(VERSION 4.2.1)

project(TETRIS CXX)

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

add_executable(${PROJECT_NAME}
  ./src/main.cpp
  ./src/Piece.cpp
  ./src/Application.cpp
  ./src/Bag.cpp
)

target_link_libraries(${PROJECT_NAME}
    raylib
)
