set(SOURCES
        src/DefaultStatisticsDb.cpp
        src/StatisticsJsonSerializer.cpp
        src/StatisticsMemoryStorage.cpp
        src/StatisticsPersistentStorage.cpp
        src/StatisticsDbFactory.cpp
        src/DefaultStatisticsDbFactory.cpp
        src/WordStatistics.cpp)

set(UT_SOURCES
        src/DefaultStatisticsDbTest.cpp
        src/StatisticsJsonSerializerTest.cpp
        src/StatisticsMemoryStorageTest.cpp
        src/StatisticsPersistentStorageTest.cpp
        src/WordStatisticsTest.cpp)

add_library(statisticsDb ${SOURCES})
add_executable(statisticsDbUT ${UT_SOURCES})

target_include_directories(statisticsDb PUBLIC "include" PRIVATE ${JSON_INCLUDE_DIR} "include/statisticsDb" ${PLOG_INCLUDE_DIR})
target_include_directories(statisticsDbUT PRIVATE "include" ${INTERNAL_LIBS_INCLUDE_PATH} ${JSON_INCLUDE_DIR} "include/statisticsDb")

target_link_libraries(statisticsDb PRIVATE utils)
target_link_libraries(statisticsDbUT PRIVATE gtest_main gmock utils statisticsDb)

target_compile_options(statisticsDb PUBLIC ${FLAGS})
target_compile_options(statisticsDbUT PUBLIC -Wall -Wextra -Werror)

add_test(statisticsDbUT statisticsDbUT --gtest_color=yes)
