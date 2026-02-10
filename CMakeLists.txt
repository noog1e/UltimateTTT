cmake_minimum_required(VERSION 3.16)
project(my_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main library / executable
add_library(my_lib
    src/Board.cpp
    src/Game.cpp
    src/GameState.cpp
    src/MarkerPositions.cpp
    src/TurnManager.cpp
    src/MoveProcessor.cpp
    src/InputController.cpp
    src/PlayerManager.cpp
    src/GameSetup.cpp
    src/Renderer.cpp
    src/AssetLoader.cpp
    src/TextManager.cpp
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
    tests/test_Board.cpp
    tests/TestingUtilities.cpp
    tests/test_GameState.cpp
    tests/test_MarkerPositions.cpp
    tests/test_WinConditions.cpp
    tests/test_TurnManager.cpp
    tests/test_MoveProcessor.cpp
    tests/test_InputController.cpp
    tests/test_PlayerManager.cpp
    tests/test_GameSetup.cpp
    tests/test_AssetLoader.cpp
)

target_link_libraries(tests
    PRIVATE
    my_lib
    Catch2::Catch2WithMain
)
