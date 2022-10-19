set(SOURCES
        src/DefaultStatisticsRepository.cpp
        src/StatisticsJsonSerializer.cpp
        src/StatisticsMemoryStorage.cpp
        src/StatisticsPersistentStorage.cpp
        src/WordStatistics.cpp
        )

set(UT_SOURCES
        src/DefaultStatisticsRepositoryTest.cpp
        src/StatisticsJsonSerializerTest.cpp
        src/StatisticsMemoryStorageTest.cpp
        src/StatisticsPersistentStorageTest.cpp
        src/WordStatisticsTest.cpp
        )

add_library(statistics ${SOURCES})
add_executable(statisticsUT ${SOURCES} ${UT_SOURCES})

target_include_directories(statistics
        PUBLIC
        "include"
        PRIVATE
        "include/statistics"
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(statisticsUT PRIVATE
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        "include/statistics"
        )

target_link_libraries(statistics PUBLIC fileSystem fmt::fmt)
target_link_libraries(statisticsUT PRIVATE
        gmock_main
        gtest
        fileSystem
        fmt::fmt
        )

target_compile_options(statistics PUBLIC ${FLAGS})
target_compile_options(statisticsUT PUBLIC ${FLAGS})

add_test(statisticsUT statisticsUT --gtest_color=yes)
