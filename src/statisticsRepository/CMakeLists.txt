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
add_executable(statisticsRepositoryUT ${UT_SOURCES})

target_include_directories(statisticsRepository PUBLIC "include" PRIVATE ${JSON_INCLUDE_DIR} "include/statisticsRepository" ${PLOG_INCLUDE_DIR})
target_include_directories(statisticsRepositoryUT PRIVATE "include" ${INTERNAL_LIBS_INCLUDE_PATH} ${JSON_INCLUDE_DIR} "include/statisticsRepository")

target_link_libraries(statisticsRepository PRIVATE utils)
target_link_libraries(statisticsRepositoryUT PRIVATE gtest_main gmock utils statisticsRepository)

target_compile_options(statisticsRepository PUBLIC ${FLAGS})
target_compile_options(statisticsRepositoryUT PUBLIC -Wall -Wextra -Werror)

add_test(statisticsRepositoryUT statisticsRepositoryUT --gtest_color=yes)
