cmake_minimum_required( VERSION 3.14 )
set( PROJECT_NAME glossary  )

project( ${PROJECT_NAME} )

set( CMAKE_BUILD_TYPE Debug )

find_package(CURL REQUIRED)

set(CURL_INCLUDE_DIR "/usr/local/include/curl")

set(CURL_LIBRARY_DIR "/usr/local/lib")


set(SOURCES
        ${CMAKE_SOURCE_DIR}/src/Main.cpp
        ${CMAKE_SOURCE_DIR}/src/Database.cpp
        ${CMAKE_SOURCE_DIR}/src/Glossary.cpp
        ${CMAKE_SOURCE_DIR}/src/HTML_Parser.cpp
        ${CMAKE_SOURCE_DIR}/src/HTML_Reader.cpp
        ${CMAKE_SOURCE_DIR}/src/Random.cpp
        ${CMAKE_SOURCE_DIR}/src/Txt_File.cpp
        ${CMAKE_SOURCE_DIR}/src/Word.cpp
        ${CMAKE_SOURCE_DIR}/src/Word_Description.cpp
        ${CMAKE_SOURCE_DIR}/src/Word_Factory.cpp
        ${CMAKE_SOURCE_DIR}/src/Word_Viewer.cpp
        )

add_executable( ${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "./include" ${CURL_INCLUDE_DIR})

target_link_directories(${PROJECT_NAME} PUBLIC ${CURL_LIBRARY_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC -lcurl)
