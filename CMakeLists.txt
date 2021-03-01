cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME glossary)
project(${PROJECT_NAME} CXX)

find_package(Qt5 COMPONENTS Core Widgets Gui Charts REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(externals)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std:c++17 /permissive- /W4")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror")
endif()

set(GMOCK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/googletest/googlemock/include")
set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/googletest/googletest/include")
set(JSON_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/json/include")
set(CURL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/curl/include")

enable_testing()

option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

if(${ENABLE_COVERAGE})
  add_compile_options(--coverage -O0)
  link_libraries(--coverage)
endif()

add_subdirectory(src)

