cmake_minimum_required( VERSION 3.14 )

set( PROJECT_NAME glossary  )
project( ${PROJECT_NAME} )

set(CMAKE_CXX_STANDARD 17)
set( CMAKE_BUILD_TYPE Debug )
set( CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address" )
set( FLAGS -std=c++17 -Wall -g3 -fno-omit-frame-pointer -pedantic-errors -Wextra -Wconversion -Werror)

find_package(Boost REQUIRED)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(googletest)
add_subdirectory(json)
add_subdirectory(curl)

set(SOURCES
        Source/WordsDatabase.cpp
        Source/Glossary.cpp
        Source/HtmlReaderImpl.cpp
        Source/Random.cpp
        Source/GlossaryHtmlParser.cpp
        Source/DefaultHtmlParser.cpp
        Source/FileAccessImpl.cpp
        Source/StringHelper.cpp
        Source/WordFactory.cpp
        Source/WordDescriptionParser.cpp
        Source/MemoryStorage.cpp
        Source/PersistentStorage.cpp
        Source/DictionaryReaderImpl.cpp
        Source/DictionaryAvailabilityHandlerImpl.cpp
        Source/WordsSerializerImpl.cpp
        )

set(UT_SOURCES
        UT/Source/TestMain.cpp
        UT/Source/HtmlReaderImplTest.cpp
        UT/Source/GlossaryHtmlParserTest.cpp
        UT/Source/DefaultHtmlParserTest.cpp
        UT/Source/FileAccessImplTest.cpp
        UT/Source/WordsDatabaseTest.cpp
        UT/Source/DictionaryReaderImplTest.cpp
        UT/Source/DictionaryAvailabilityHandlerImplTest.cpp
        UT/Source/MemoryStorageTest.cpp
        UT/Source/PersistentStorageTest.cpp
        UT/Source/WordsSerializerImplTest.cpp
        )

add_executable( ${PROJECT_NAME} ${SOURCES} Source/Main.cpp)
add_executable(executeTests ${UT_SOURCES} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "Include" "UT/Doubles" )
target_include_directories(executeTests PUBLIC "Include" "UT/Doubles")

target_link_libraries(${PROJECT_NAME} PUBLIC -lcurl ${Boost_LIBRARIES} nlohmann_json)
target_link_libraries(executeTests PUBLIC -lcurl gtest gmock pthread nlohmann_json)

target_compile_options(${PROJECT_NAME} PUBLIC ${FLAGS})
target_compile_options(executeTests PUBLIC -Wall -Wextra -Wpedantic -Werror)
