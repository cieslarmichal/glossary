set(SOURCES
        Source/TranslationServiceImpl.cpp
        Source/WordDescriptionServiceImpl.cpp
        Source/DescriptionParserImpl.cpp
        Source/Glossary.cpp
        Source/GlossaryHtmlParserImpl.cpp
        Source/DictionaryReaderImpl.cpp
        Source/HttpWordDescriptionCreatorImpl.cpp
        Source/WordDescriptionConcurrentGenerator.cpp
        Source/WordViewerImpl.cpp
        Source/UserPromptImpl.cpp
        Source/AnswerCheckerImpl.cpp
        Source/GlossaryApplication.cpp
        Source/WordRandomizerImpl.cpp
        Source/WordsBuilderImpl.cpp
        )

set(UT_SOURCES
        UT/Source/TranslationServiceImplTest.cpp
        UT/Source/WordDescriptionServiceImplTest.cpp
        UT/Source/DescriptionParserImplTest.cpp
        UT/Source/GlossaryHtmlParserImplTest.cpp
        UT/Source/DictionaryReaderImplTest.cpp
        UT/Source/HttpWordDescriptionCreatorImplTest.cpp
        UT/Source/WordViewerImplTest.cpp
        UT/Source/UserPromptImplTest.cpp
        UT/Source/AnswerCheckerImplTest.cpp
        UT/Source/WordDescriptionConcurrentGeneratorTest.cpp
        UT/Source/WordsBuilderImplTest.cpp
        )

add_executable(glossary ${SOURCES} Source/Main.cpp)
add_executable(glossaryUT ${UT_SOURCES} ${SOURCES})

target_include_directories(glossary PUBLIC "Include" PRIVATE)
target_include_directories(glossaryUT PUBLIC "Include" "UT/Doubles" "UT/")

target_link_libraries(glossary PUBLIC ${Boost_LIBRARIES} nlohmann_json webConnection translationsDb statisticsDb translator wordsDescriptionsDb utils)
target_link_libraries(glossaryUT PUBLIC gtest_main gmock pthread nlohmann_json webConnection translationsDb statisticsDb translator wordsDescriptionsDb utils)

target_compile_options(glossary PUBLIC ${FLAGS})
target_compile_options(glossaryUT PUBLIC -Wall -Wextra -Werror)

add_test(glossaryUT glossaryUT --gtest_color=yes)