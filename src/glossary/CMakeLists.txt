set(SOURCES
        src/WordDescriptionConcurrentUpdater.cpp
        src/DefaultAnswerValidator.cpp
        src/DefaultGlossary.cpp
        src/GlossaryFactory.cpp
        src/DefaultGlossaryFactory.cpp
        src/TranslationConcurrentUpdater.cpp
        src/DefaultDictionaryTranslationUpdater.cpp
        src/ExternalServicesConnectionChecker.cpp
        src/DefaultDictionaryStatisticsCounter.cpp
        )

set(UT_SOURCES
        src/DefaultAnswerValidatorTest.cpp
        src/WordDescriptionConcurrentUpdaterTest.cpp
        src/TranslationConcurrentUpdaterTest.cpp
        src/DefaultDictionaryTranslationUpdaterTest.cpp
        src/DefaultGlossaryTest.cpp
        src/ExternalServicesConnectionCheckerTest.cpp
        src/DefaultDictionaryStatisticsCounterTest.cpp
        )

add_library(glossary ${SOURCES})
add_executable(glossaryUT ${SOURCES} ${UT_SOURCES})

target_compile_definitions(glossaryUT PUBLIC -DGTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(glossary PUBLIC "include")
target_include_directories(glossaryUT PUBLIC "include")

target_link_libraries(glossary PUBLIC
        ${Boost_LIBRARIES}
        httpClient
        wordDescriptionService
        dictionaryService
        translationService
        translationRepository
        statisticsRepository
        translator
        wordDescriptionRepository
        wordDescriptionDownloader
        utils
        )
target_link_libraries(glossaryUT PUBLIC
        gmock_main
        gtest
        httpClient
        wordDescriptionService
        dictionaryService
        translationService
        translationRepository
        statisticsRepository
        translator
        wordDescriptionRepository
        wordDescriptionDownloader
        utils
        )

target_compile_options(glossary PUBLIC ${FLAGS})
target_compile_options(glossaryUT PUBLIC)

add_test(glossaryUT glossaryUT --gtest_color=yes)