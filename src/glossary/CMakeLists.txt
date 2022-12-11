set(SOURCES
        src/WordDescriptionConcurrentUpdater.cpp
        src/DefaultGlossary.cpp
        src/GlossaryFactory.cpp
        src/DefaultGlossaryFactory.cpp
        src/TranslationConcurrentUpdater.cpp
        src/DefaultDictionaryStatisticsCounter.cpp
        )

set(UT_SOURCES
        src/WordDescriptionConcurrentUpdaterTest.cpp
        src/TranslationConcurrentUpdaterTest.cpp
        src/DefaultDictionaryStatisticsCounterTest.cpp
        )

add_library(glossary ${SOURCES})
add_executable(glossaryUT ${SOURCES} ${UT_SOURCES})

target_include_directories(glossary PUBLIC "include")
target_include_directories(glossaryUT PUBLIC "include")

target_link_libraries(glossary PUBLIC
        ${Boost_LIBRARIES}
        httpClient
        collection
        dictionary
        statistics
        translation
        fileSystem
        )
target_link_libraries(glossaryUT PUBLIC
        gmock_main
        gtest
        httpClient
        collection
        dictionary
        statistics
        translation
        fileSystem
        )

target_compile_options(glossary PUBLIC ${FLAGS})
target_compile_options(glossaryUT PUBLIC ${FLAGS})

add_test(glossaryUT glossaryUT --gtest_color=yes)
