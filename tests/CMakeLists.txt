cmake_minimum_required(VERSION 3.16)
project(physi_tests)


include(CTest)
include(FetchContent)


FetchContent_Declare(
Catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(Catch2)


add_executable(unit_tests test_units.cpp)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain physi)


add_test(NAME unit_tests COMMAND unit_tests)