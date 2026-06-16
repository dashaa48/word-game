cmake_minimum_required(VERSION 3.14...3.31)

project(word_game VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG        v2.4.11
)
FetchContent_MakeAvailable(doctest)

add_executable(word_game
    src/main.cpp
    src/game.cpp
    src/dictionary.cpp
    src/player.cpp
    src/utils.cpp
)

target_include_directories(word_game PRIVATE src)

add_executable(word_game_tests
    tests/test_game.cpp
    src/game.cpp
    src/dictionary.cpp
    src/player.cpp
    src/utils.cpp
)

target_include_directories(word_game_tests PRIVATE src tests)
target_link_libraries(word_game_tests PRIVATE doctest::doctest)

include(CTest)
enable_testing()
add_test(NAME word_game_unit_tests COMMAND word_game_tests)