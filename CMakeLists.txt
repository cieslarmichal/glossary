cmake_minimum_required( VERSION 3.14 )
set( PROJECT_NAME glossary  )

project( ${PROJECT_NAME} )

set( CMAKE_BUILD_TYPE Debug )


set( CMAKE_CXX_FLAGS_DEBUG "-std=c++17 -Wall -g3 -fsanitize=address -fno-omit-frame-pointer -pedantic-errors -Wextra -Wconversion" )
# -Werror

find_package(CURL REQUIRED)
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

set(CURL_INCLUDE_DIR "/usr/local/include/curl")
set(CURL_LIBRARY_DIR "/usr/local/lib")


set(SOURCES
        Source/DatabaseImpl.cpp
        Source/Glossary.cpp
        Source/HtmlReaderImpl.cpp
        Source/Random.cpp
        Source/Word.cpp
        Source/Word_Description.cpp
        Source/Word_Factory.cpp
        Source/Word_Viewer.cpp
        Source/GlossaryHtmlParser.cpp
        Source/DefaultHtmlParser.cpp
        Source/FileAccessImpl.cpp
        )

set(UT
        UT/Source/TestMain.cpp
        UT/Source/HtmlReaderImplTest.cpp
        UT/Source/GlossaryHtmlParserTest.cpp
        UT/Source/DefaultHtmlParserTest.cpp
        UT/Source/FileAccessImplTest.cpp
        UT/Source/DatabaseImplTest.cpp
        )

add_executable( ${PROJECT_NAME} ${SOURCES} Source/Main.cpp)
add_executable(executeTests ${UT} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "Include" "UT/Doubles" ${CURL_INCLUDE_DIR})

target_include_directories(executeTests PUBLIC "Include" "UT/Doubles")

target_link_directories(${PROJECT_NAME} PUBLIC ${CURL_LIBRARY_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC -lcurl)
target_link_libraries(executeTests PUBLIC -lcurl ${GTEST_LIBRARIES} pthread)
