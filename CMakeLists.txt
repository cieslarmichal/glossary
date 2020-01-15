cmake_minimum_required( VERSION 3.12.4 )

set( PROJECT_NAME glossary  )
project( ${PROJECT_NAME} )

enable_testing()

add_subdirectory(externals)

set(CMAKE_CXX_STANDARD 17)
set( CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address" )
set( FLAGS -std=c++17 -Wall -g3 -fno-omit-frame-pointer -pedantic-errors -Wextra -Wconversion -Werror)

option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

if(${ENABLE_COVERAGE})
  add_compile_options(--coverage -O0 -g)
  link_libraries(--coverage)
endif()

set(SOURCES
        Source/wordsDb/descriptionsDb/WordsDatabase.cpp
        Source/Glossary.cpp
        Source/webConnection/HttpRequestHandlerImpl.cpp
        Source/translation/TranslatorImpl.cpp
        Source/translation/TranslationDeserializerImpl.cpp
        Source/GlossaryHtmlParser.cpp
        Source/DefaultHtmlParser.cpp
        Source/FileAccessImpl.cpp
        Source/StringHelper.cpp
        Source/WordDescriptionParser.cpp
        Source/wordsDb/MemoryStorage.cpp
        Source/wordsDb/PersistentStorage.cpp
        Source/DictionaryReaderImpl.cpp
        Source/wordsDb/descriptionsDb/WordsSerializerImpl.cpp
        Source/WordDescriptionSerializer.cpp
        Source/HtmlWordsCreatorImpl.cpp
        Source/WordsGeneratorServiceImpl.cpp
        Source/wordsDb/statisticsDb/StatisticsDbImpl.cpp
        Source/wordsDb/statisticsDb/StatisticsSerializerImpl.cpp
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
        UT/Source/webConnection/HttpRequestHandlerTest.cpp
        UT/Source/GlossaryHtmlParserTest.cpp
        UT/Source/DefaultHtmlParserTest.cpp
        UT/Source/FileAccessImplTest.cpp
        UT/Source/wordsDb/descriptionsDb/WordsDatabaseTest.cpp
        UT/Source/DictionaryReaderImplTest.cpp
        UT/Source/wordsDb/MemoryStorageTest.cpp
        UT/Source/wordsDb/PersistentStorageTest.cpp
        UT/Source/wordsDb/descriptionsDb/WordsSerializerImplTest.cpp
        UT/Source/WordDescriptionSerializerTest.cpp
        UT/Source/WordDescriptionParserTest.cpp
        UT/Source/HtmlWordsCreatorImplTest.cpp
        UT/Source/wordsDb/statisticsDb/StatisticsDbImplTest.cpp
        UT/Source/wordsDb/statisticsDb/StatisticsSerializerImplTest.cpp
        UT/Source/WordsShufflerImplTest.cpp
        UT/Source/WordViewerImplTest.cpp
        UT/Source/UserPromptImplTest.cpp
        UT/Source/AnswerCheckerImplTest.cpp
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
