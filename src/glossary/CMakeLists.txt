set(SOURCES
        Source/DefaultTranslationRetrieverService.cpp
        Source/DefaultWordDescriptionRetrieverService.cpp
        Source/Glossary.cpp
        Source/WordDescriptionConcurrentGenerator.cpp
        Source/DefaultWordViewFormatter.cpp
        Source/UserStandardInputPrompt.cpp
        Source/DefaultAnswerValidator.cpp
        Source/GlossaryApplication.cpp
        Source/WordMersenneTwisterRandomizer.cpp
        Source/DefaultWordsMerger.cpp
        Source/WordDescriptionCorrespondingToEnglishWordFinder.cpp
        Source/WordCreator.cpp
        Source/SupportedThreadsCalculator.cpp
        )

set(UT_SOURCES
        UT/Source/DefaultTranslationRetrieverServiceTest.cpp
        UT/Source/DefaultWordDescriptionRetrieverServiceTest.cpp
        UT/Source/DefaultWordViewFormatterTest.cpp
        UT/Source/DefaultAnswerValidatorTest.cpp
        UT/Source/WordDescriptionConcurrentGeneratorTest.cpp
        UT/Source/DefaultWordsMergerTest.cpp
        UT/Source/WordDescriptionCorrespondingToEnglishWordFinderTest.cpp
        UT/Source/WordCreatorTest.cpp
        )

add_executable(glossary ${SOURCES} Source/Main.cpp)
add_executable(glossaryUT ${UT_SOURCES} ${SOURCES})

target_include_directories(glossary PUBLIC "Include" PRIVATE)
target_include_directories(glossaryUT PUBLIC "Include" "UT/Doubles" "UT/")

target_link_libraries(glossary PUBLIC ${Boost_LIBRARIES} nlohmann_json webConnection dictionaryRepository translationRepository statisticsRepository translator wordDescriptionRepository wordDescriptionDownloader utils)
target_link_libraries(glossaryUT PUBLIC gtest_main gmock pthread nlohmann_json webConnection dictionaryRepository translationRepository statisticsRepository translator wordDescriptionRepository wordDescriptionDownloader utils)

target_compile_options(glossary PUBLIC ${FLAGS})
target_compile_options(glossaryUT PUBLIC -Wall -Wextra -Werror)

add_test(glossaryUT glossaryUT --gtest_color=yes)