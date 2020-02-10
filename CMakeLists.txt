cmake_minimum_required( VERSION 3.12.4 )

set( PROJECT_NAME glossary  )
project( ${PROJECT_NAME} )

enable_testing()

add_subdirectory(externals)

set(CMAKE_CXX_STANDARD 20)
set( CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address" )
set( FLAGS -std=c++17 -Wall -g3 -fno-omit-frame-pointer -pedantic-errors -Wextra -Wconversion -Werror)

option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

if(${ENABLE_COVERAGE})
  add_compile_options(--coverage -O0 -g)
  link_libraries(--coverage)
endif()

set(SOURCES
        Source/translation/TranslatorImpl.cpp
        Source/translation/TranslationDeserializerImpl.cpp
        Source/translation/TranslationRequestFormatterImpl.cpp
        Source/webConnection/HttpRequestHandlerImpl.cpp
        Source/wordsDb/wordsDescriptionsDb/WordsDescriptionsDbImpl.cpp
        Source/wordsDb/wordsDescriptionsDb/WordsDescriptionsMemoryStorage.cpp
        Source/wordsDb/wordsDescriptionsDb/WordsDescriptionsPersistentStorage.cpp
        Source/wordsDb/wordsDescriptionsDb/WordsDescriptionsSerializerImpl.cpp
        Source/wordsDb/wordsDescriptionsDb/DescriptionSerializer.cpp
        Source/wordsDb/statisticsDb/StatisticsDbImpl.cpp
        Source/wordsDb/statisticsDb/StatisticsSerializerImpl.cpp
        Source/wordsDb/statisticsDb/StatisticsMemoryStorage.cpp
        Source/wordsDb/statisticsDb/StatisticsPersistentStorage.cpp
        Source/wordsDb/translationsDb/TranslationsDbImpl.cpp
        Source/wordsDb/translationsDb/TranslationsSerializerImpl.cpp
        Source/wordsDb/translationsDb/TranslationsMemoryStorage.cpp
        Source/wordsDb/translationsDb/TranslationsPersistentStorage.cpp
        Source/wordsDb/WordsDbImpl.cpp
        Source/TranslationServiceImpl.cpp
        Source/DescriptionParserImpl.cpp
        Source/Glossary.cpp
        Source/GlossaryHtmlParserImpl.cpp
        Source/utils/HtmlTagsDeleter.cpp
        Source/utils/FileAccessImpl.cpp
        Source/utils/StringHelper.cpp
        Source/DictionaryReaderImpl.cpp
        Source/HttpWordDescriptionCreatorImpl.cpp
        Source/WordsGeneratorServiceImpl.cpp
        Source/WordsShufflerImpl.cpp
        Source/WordViewerImpl.cpp
        Source/UserPromptImpl.cpp
        Source/AnswerCheckerImpl.cpp
        Source/GlossaryApplication.cpp
        Source/WordRandomizerImpl.cpp
        )

set(UT_SOURCES
        UT/Source/translation/TranslatorImplTest.cpp
        UT/Source/translation/TranslationDeserializerImplTest.cpp
        UT/Source/translation/TranslationRequestFormatterImplTest.cpp
        UT/Source/webConnection/HttpRequestHandlerTest.cpp
        UT/Source/wordsDb/wordsDescriptionsDb/WordsDescriptionsDbImplTest.cpp
        UT/Source/wordsDb/wordsDescriptionsDb/WordsDescriptionsMemoryStorageTest.cpp
        UT/Source/wordsDb/wordsDescriptionsDb/WordsDescriptionsPersistentStorageTest.cpp
        UT/Source/wordsDb/wordsDescriptionsDb/WordsDescriptionsSerializerImplTest.cpp
        UT/Source/wordsDb/wordsDescriptionsDb/DescriptionSerializerTest.cpp
        UT/Source/wordsDb/statisticsDb/StatisticsDbImplTest.cpp
        UT/Source/wordsDb/statisticsDb/StatisticsSerializerImplTest.cpp
        UT/Source/wordsDb/statisticsDb/StatisticsMemoryStorageTest.cpp
        UT/Source/wordsDb/statisticsDb/StatisticsPersistentStorageTest.cpp
        UT/Source/wordsDb/translationsDb/TranslationsDbImplTest.cpp
        UT/Source/wordsDb/translationsDb/TranslationsSerializerImplTest.cpp
        UT/Source/wordsDb/translationsDb/TranslationsMemoryStorageTest.cpp
        UT/Source/wordsDb/translationsDb/TranslationsPersistentStorageTest.cpp
        UT/Source/wordsDb/WordsDbImplTest.cpp
        UT/Source/TranslationServiceImplTest.cpp
        UT/Source/DescriptionParserImplTest.cpp
        UT/Source/GlossaryHtmlParserImplTest.cpp
        UT/Source/utils/HtmlTagsDeleterTest.cpp
        UT/Source/utils/FileAccessImplTest.cpp
        UT/Source/DictionaryReaderImplTest.cpp
        UT/Source/HttpWordDescriptionCreatorImplTest.cpp
        UT/Source/WordsShufflerImplTest.cpp
        UT/Source/WordViewerImplTest.cpp
        UT/Source/UserPromptImplTest.cpp
        UT/Source/AnswerCheckerImplTest.cpp
        UT/Source/utils/StringHelperTest.cpp
        )

add_executable( ${PROJECT_NAME} ${SOURCES} Source/Main.cpp)
add_executable(executeTests ${UT_SOURCES} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "Include" "UT/Doubles" )
target_include_directories(executeTests PUBLIC "Include" "UT/Doubles" "UT/")

target_link_libraries(${PROJECT_NAME} PUBLIC -lcurl ${Boost_LIBRARIES} nlohmann_json)
target_link_libraries(executeTests PUBLIC -lcurl gtest_main gmock pthread nlohmann_json)

target_compile_options(${PROJECT_NAME} PUBLIC ${FLAGS})
target_compile_options(executeTests PUBLIC -Wall -Wextra -Wpedantic -Werror)

add_test(executeTests ${CMAKE_BINARY_DIR}/executeTests --gtest_color=yes)
