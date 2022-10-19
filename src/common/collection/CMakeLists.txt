set(SOURCES
        src/StringHelper.cpp
        include/collection/StlOperators.h
        )

set(UT_SOURCES
        src/StringHelperTest.cpp
        src/ThreadSafeQueueTest.cpp
        )

add_library(collection ${SOURCES})
add_executable(collectionUT ${SOURCES} ${UT_SOURCES})

target_include_directories(collection
        PUBLIC
        "include"
        PRIVATE
        "include/collection"
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(collectionUT PRIVATE
        "include/collection"
        ${Boost_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        )

target_link_libraries(collectionUT PRIVATE gtest_main)

target_compile_options(collection PUBLIC ${FLAGS})
target_compile_options(collectionUT PUBLIC ${FLAGS})

add_test(collectionUT collectionUT --gtest_color=yes)
