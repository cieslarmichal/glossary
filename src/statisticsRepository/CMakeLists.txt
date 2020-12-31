set(SOURCES
        src/DefaultStatisticsRepository.cpp
        src/StatisticsJsonSerializer.cpp
        src/StatisticsMemoryStorage.cpp
        src/StatisticsPersistentStorage.cpp
        src/StatisticsRepositoryFactory.cpp
        src/DefaultStatisticsRepositoryFactory.cpp
        src/WordStatistics.cpp)

set(UT_SOURCES
        src/DefaultStatisticsRepositoryTest.cpp
        src/StatisticsJsonSerializerTest.cpp
        src/StatisticsMemoryStorageTest.cpp
        src/StatisticsPersistentStorageTest.cpp
        src/WordStatisticsTest.cpp)

add_library(statisticsRepository ${SOURCES})
add_executable(statisticsRepositoryUT ${SOURCES} ${UT_SOURCES})

target_compile_definitions(statisticsRepositoryUT PUBLIC -DGTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(statisticsRepository
        PUBLIC
        "include"
        PRIVATE
        "include/statisticsRepository"
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(statisticsRepositoryUT PRIVATE
        "include"
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        "include/statisticsRepository"
        )

target_link_libraries(statisticsRepository PUBLIC utils)
target_link_libraries(statisticsRepositoryUT PRIVATE
        gmock_main
        gtest
        utils
        )

target_compile_options(statisticsRepository PUBLIC ${FLAGS})
target_compile_options(statisticsRepositoryUT PUBLIC)

add_test(statisticsRepositoryUT statisticsRepositoryUT --gtest_color=yes)
