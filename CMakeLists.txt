cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME glossary)
project(${PROJECT_NAME})

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)
add_subdirectory(externals)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address")
set(FLAGS -std=c++17 -Wall -g3 -fno-omit-frame-pointer -Wextra -Werror)

set(GMOCK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/googletest/googlemock/include")
set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/googletest/googletest/include")
set(JSON_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/json/include")
set(CURL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/curl/include/curl")

enable_testing()

option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

if(${ENABLE_COVERAGE})
  add_compile_options(--coverage -O0)
  link_libraries(--coverage)
endif()

add_subdirectory(src)


