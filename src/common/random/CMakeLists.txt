set(SOURCES
        src/RandomNumberMersenneTwisterGenerator.cpp
        )

set(UT_SOURCES
        src/RandomNumberMersenneTwisterGeneratorTest.cpp
        )


add_library(random ${SOURCES})
add_executable(randomUT ${SOURCES} ${UT_SOURCES})

target_include_directories(random
        PUBLIC "include"
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(randomUT PRIVATE
        "include"
        ${Boost_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        )

target_link_libraries(random PUBLIC)

target_link_libraries(randomUT PRIVATE gtest_main)

target_compile_options(random PUBLIC ${FLAGS})
target_compile_options(randomUT PUBLIC ${FLAGS})

add_test(randomUT randomUT --gtest_color=yes)
