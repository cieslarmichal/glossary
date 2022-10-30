set(SOURCES
        src/repositories/DefaultStatisticsRepository.cpp
        src/serializers/WordsStatisticsJsonSerializer.cpp
        src/repositories/StatisticsMemoryStorage.cpp
        src/repositories/StatisticsPersistentStorage.cpp
        src/commands/AddWordStatisticsCommandImpl.cpp
        src/commands/AddCorrectAnswerCommandImpl.cpp
        src/commands/AddIncorrectAnswerCommandImpl.cpp
        src/commands/ResetWordsStatisticsCommandImpl.cpp
        src/queries/GetWordsStatisticsQueryImpl.cpp
        )

set(UT_SOURCES
        src/repositories/DefaultStatisticsRepositoryTest.cpp
        src/serializers/WordsStatisticsJsonSerializerTest.cpp
        src/repositories/StatisticsMemoryStorageTest.cpp
        src/repositories/StatisticsPersistentStorageTest.cpp
        src/commands/AddWordStatisticsCommandImplTest.cpp
        src/commands/AddCorrectAnswerCommandImplTest.cpp
        src/commands/AddIncorrectAnswerCommandImplTest.cpp
        src/commands/ResetWordsStatisticsCommandImplTest.cpp
        src/queries/GetWordsStatisticsQueryImplTest.cpp
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
