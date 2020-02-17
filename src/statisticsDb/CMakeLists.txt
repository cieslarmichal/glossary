set(SOURCES
        src/StatisticsDbImpl.cpp
        src/StatisticsSerializerImpl.cpp
        src/StatisticsMemoryStorage.cpp
        src/StatisticsPersistentStorage.cpp
        src/StatisticsDbFactory.cpp
        src/StatisticsDbFactoryImpl.cpp)

set(UT_SOURCES
        src/StatisticsDbImplTest.cpp
        src/StatisticsSerializerImplTest.cpp
        src/StatisticsMemoryStorageTest.cpp
        src/StatisticsPersistentStorageTest.cpp)

add_library(statisticsDb ${SOURCES})
add_executable(statisticsDbUT ${UT_SOURCES} ${SOURCES})

target_include_directories(statisticsDb PUBLIC "include" PRIVATE ${JSON_INCLUDE_DIR} "include/statisticsDb")
target_include_directories(statisticsDbUT PRIVATE "include" ${INTERNAL_LIBS_INCLUDE_PATH} ${JSON_INCLUDE_DIR} "include/statisticsDb")

target_link_libraries(statisticsDb PRIVATE utils)
target_link_libraries(statisticsDbUT PRIVATE gtest_main gmock utils)

target_compile_options(statisticsDb PUBLIC ${FLAGS})
target_compile_options(statisticsDbUT PUBLIC -Wall -Wextra -Werror)

add_test(statisticsDbUT ${EXECUTABLE_OUTPUT_PATH}/statisticsDbUT --gtest_color=yes)
