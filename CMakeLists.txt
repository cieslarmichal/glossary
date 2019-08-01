cmake_minimum_required( VERSION 3.14 )
set( PROJECT_NAME glossary  )

project( ${PROJECT_NAME} )

set( CMAKE_BUILD_TYPE Debug )

find_package(CURL REQUIRED)
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

set(CURL_INCLUDE_DIR "/usr/local/include/curl")
set(CURL_LIBRARY_DIR "/usr/local/lib")


set(SOURCES
        Source/Database.cpp
        Source/Glossary.cpp
        Source/HtmlFileReader.cpp
        Source/Random.cpp
        Source/TextFileReader.cpp
        Source/Word.cpp
        Source/Word_Description.cpp
        Source/Word_Factory.cpp
        Source/Word_Viewer.cpp
        Source/HtmlParserImpl.cpp
        Source/TextFileWriter.cpp
        )

set(UT
        UT/Source/TestMain.cpp
        UT/Source/TextFileReaderTest.cpp
        UT/Source/HtmlFileReaderTest.cpp
        UT/Source/HtmlParserImplTest.cpp
        UT/Source/TextFileWriterTest.cpp
        )

add_executable( ${PROJECT_NAME} ${SOURCES} Source/Main.cpp)
add_executable(executeTests ${UT} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "Include" "UT/Include/Doubles" ${CURL_INCLUDE_DIR})

target_include_directories(executeTests PUBLIC "Include" "UT/Include/Doubles")

target_link_directories(${PROJECT_NAME} PUBLIC ${CURL_LIBRARY_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC -lcurl)
target_link_libraries(executeTests PUBLIC -lcurl ${GTEST_LIBRARIES} pthread)
