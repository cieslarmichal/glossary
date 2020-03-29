set(SOURCES
        Source/DefaultTranslationRetrieverService.cpp
        Source/DefaultWordDescriptionRetrieverService.cpp
        Source/Glossary.cpp
        ../dictionaryRepository/src/DefaultDictionaryReader.cpp
        Source/WordDescriptionConcurrentGenerator.cpp
        Source/DefaultWordViewFormatter.cpp
        Source/UserStandardInputPrompt.cpp
        Source/DefaultAnswerValidator.cpp
        Source/GlossaryApplication.cpp
        Source/WordMersenneTwisterRandomizer.cpp
        Source/DefaultWordsMerger.cpp
        Source/WordDescriptionCorrespondingToEnglishWordFinder.cpp
        Source/WordCreator.cpp
        ../dictionaryRepository/src/DefaultDictionaryRepository.cpp
        Source/SupportedThreadsCalculator.cpp
        Source/DefaultStatisticsModifierService.cpp
        )

set(UT_SOURCES
        UT/Source/DefaultTranslationRetrieverServiceTest.cpp
        UT/Source/DefaultWordDescriptionRetrieverServiceTest.cpp
        ../dictionaryRepository/src/DefaultDictionaryReaderTest.cpp
        UT/Source/DefaultWordViewFormatterTest.cpp
        UT/Source/DefaultAnswerValidatorTest.cpp
        UT/Source/WordDescriptionConcurrentGeneratorTest.cpp
        UT/Source/DefaultWordsMergerTest.cpp
        UT/Source/WordDescriptionCorrespondingToEnglishWordFinderTest.cpp
        UT/Source/WordCreatorTest.cpp
        ../dictionaryRepository/src/DefaultDictionaryRepositoryTest.cpp
        UT/Source/DefaultStatisticsModifierServiceTest.cpp
        )

add_executable(glossary ${SOURCES} Source/Main.cpp)
add_executable(glossaryUT ${UT_SOURCES} ${SOURCES})

target_include_directories(glossary PUBLIC "Include" PRIVATE)
target_include_directories(glossaryUT PUBLIC "Include" "UT/Doubles" "UT/")

target_link_libraries(glossary PUBLIC ${Boost_LIBRARIES} nlohmann_json webConnection translationRepository statisticsRepository translator wordDescriptionRepository wordDescriptionDownloader utils)
target_link_libraries(glossaryUT PUBLIC gtest_main gmock pthread nlohmann_json webConnection translationRepository statisticsRepository translator wordDescriptionRepository wordDescriptionDownloader utils)

target_compile_options(glossary PUBLIC ${FLAGS})
target_compile_options(glossaryUT PUBLIC -Wall -Wextra -Werror)

add_test(glossaryUT glossaryUT --gtest_color=yes)