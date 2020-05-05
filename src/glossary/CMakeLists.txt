set(SOURCES
        Source/GlossaryApplication.cpp
        Source/WordDescriptionConcurrentUpdater.cpp
        Source/DefaultWordViewFormatter.cpp
        Source/UserStandardInputPrompt.cpp
        Source/DefaultAnswerValidator.cpp
        Source/DefaultGlossary.cpp
        Source/GlossaryFactory.cpp
        Source/DefaultGlossaryFactory.cpp
        Source/TranslationConcurrentUpdater.cpp
        Source/DefaultDictionaryTranslationUpdater.cpp
        Source/MerriamWebsterConnectionChecker.cpp
        )

set(UT_SOURCES
        UT/Source/DefaultWordViewFormatterTest.cpp
        UT/Source/DefaultAnswerValidatorTest.cpp
        UT/Source/WordDescriptionConcurrentUpdaterTest.cpp
        UT/Source/TranslationConcurrentUpdaterTest.cpp
        UT/Source/DefaultDictionaryTranslationUpdaterTest.cpp
        UT/Source/MerriamWebsterConnectionCheckerTest.cpp
        UT/Source/DefaultGlossaryTest.cpp
        )

add_executable(glossary ${SOURCES} Source/Main.cpp)
add_executable(glossaryUT ${UT_SOURCES} ${SOURCES})

target_include_directories(glossary PUBLIC "Include" PRIVATE)
target_include_directories(glossaryUT PUBLIC "Include" "UT/Doubles" "UT/")

target_link_libraries(glossary PUBLIC ${Boost_LIBRARIES} nlohmann_json webConnection wordDescriptionService dictionaryService translationService translationRepository statisticsRepository translator wordDescriptionRepository wordDescriptionDownloader utils)
target_link_libraries(glossaryUT PUBLIC gtest_main gmock pthread nlohmann_json webConnection wordDescriptionService dictionaryService translationService translationRepository statisticsRepository translator wordDescriptionRepository wordDescriptionDownloader utils)

target_compile_options(glossary PUBLIC ${FLAGS})
target_compile_options(glossaryUT PUBLIC -Wall -Wextra -Werror)

add_test(glossaryUT glossaryUT --gtest_color=yes)