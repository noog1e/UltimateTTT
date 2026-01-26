cmake_minimum_required(VERSION 3.16)
project(my_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main library / executable
add_library(my_lib
    src/board.cpp
    src/game.cpp
    src/GameState.cpp
    src/MarkerPositions.cpp
)

target_include_directories(my_lib PUBLIC src)

# Fetch Catch2
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Tests
add_executable(tests
    tests/test_GameState.cpp
    tests/test_MarkerPositions.cpp
    tests/test_WinConditions.cpp
    tests/test_TurnManager.cpp
)

target_link_libraries(tests
    PRIVATE
    my_lib
    Catch2::Catch2WithMain
)
