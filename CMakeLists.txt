cmake_minimum_required(VERSION 3.16)
project(physi VERSION 0.1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(physi INTERFACE)
target_include_directories(physi INTERFACE
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>
)
target_compile_features(physi INTERFACE cxx_constexpr)


add_executable(example_app examples/minimal_example.cpp)
target_link_libraries(example_app PRIVATE physi)
set_target_properties(example_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include(CTest)
add_subdirectory(tests)


include(GNUInstallDirs)
install(TARGETS physi EXPORT physiTargets
INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT physiTargets
FILE physiTargets.cmake
NAMESPACE physi::
DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/physi)