cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME glossary)
project(${PROJECT_NAME} CXX)

find_package(Qt5 COMPONENTS Core Widgets Gui Charts REQUIRED)

add_subdirectory(externals)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -Werror")

set(GMOCK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/googletest/googlemock/include")
set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/googletest/googletest/include")
set(JSON_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/json/include")
set(CPR_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/cpr/include")
set(DOTENV_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/dotenv-cpp/include")

enable_testing()

add_subdirectory(src)
