set(SOURCES
        src/GlossaryApplication.cpp
        src/WordDescriptionConcurrentUpdater.cpp
        src/DefaultWordViewFormatter.cpp
        src/UserStandardInputPrompt.cpp
        src/DefaultAnswerValidator.cpp
        src/DefaultGlossary.cpp
        src/GlossaryFactory.cpp
        src/DefaultGlossaryFactory.cpp
        src/TranslationConcurrentUpdater.cpp
        src/DefaultDictionaryTranslationUpdater.cpp
        src/MerriamWebsterConnectionChecker.cpp
        )

set(UT_SOURCES
        src/DefaultWordViewFormatterTest.cpp
        src/DefaultAnswerValidatorTest.cpp
        src/WordDescriptionConcurrentUpdaterTest.cpp
        src/TranslationConcurrentUpdaterTest.cpp
        src/DefaultDictionaryTranslationUpdaterTest.cpp
        src/MerriamWebsterConnectionCheckerTest.cpp
        src/DefaultGlossaryTest.cpp
        )

add_library(glossary ${SOURCES})
add_executable(glossaryUT ${UT_SOURCES})

target_include_directories(glossary PUBLIC "include")
target_include_directories(glossaryUT PUBLIC "include")

target_link_libraries(glossary PUBLIC
        ${Boost_LIBRARIES}
        nlohmann_json
        webConnection
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
        gtest_main
        gmock
        pthread
        nlohmann_json
        webConnection
        wordDescriptionService
        dictionaryService
        translationService
        translationRepository
        statisticsRepository
        translator
        wordDescriptionRepository
        wordDescriptionDownloader
        utils
        glossary
        )

target_compile_options(glossary PUBLIC ${FLAGS})
target_compile_options(glossaryUT PUBLIC -Wall -Wextra -Werror)

add_test(glossaryUT glossaryUT --gtest_color=yes)