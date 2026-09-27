cmake_minimum_required(VERSION 3.24)
project(toychain LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

add_library(toychain_warnings INTERFACE)
if(NOT MSVC)
  target_compile_options(toychain_warnings INTERFACE
    -Wall -Wextra -Wpedantic -Wshadow)
endif()

add_library(toychain src/hash.cpp)
target_include_directories(toychain PUBLIC include)
target_compile_features(toychain PUBLIC cxx_std_20)
target_link_libraries(toychain PRIVATE toychain_warnings)
if(NOT APPLE)
  find_package(OpenSSL REQUIRED)
  target_link_libraries(toychain PRIVATE OpenSSL::Crypto)
endif()

enable_testing()
include(FetchContent)
FetchContent_Declare(googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(toychain_tests tests/hash_test.cpp)
target_link_libraries(toychain_tests PRIVATE toychain toychain_warnings GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(toychain_tests DISCOVERY_MODE PRE_TEST)
