
set(SOURCES
        src/DefaultWordDescriptionService.cpp
        src/WordDescriptionServiceFactory.cpp
        src/DefaultWordDescriptionServiceFactory.cpp
        src/DefaultWordsApiConnectionChecker.cpp
        src/WordsApiKeyFileReader.cpp
        src/ApiKeyFileFormatter.cpp
        src/DefaultApiKeyLocationUpdater.cpp
        )

set(UT_SOURCES
        src/DefaultWordDescriptionServiceTest.cpp
        src/DefaultWordsApiConnectionCheckerTest.cpp
        src/WordsApiKeyFileReaderTest.cpp
        src/ApiKeyFileFormatterTest.cpp
        src/DefaultApiKeyLocationUpdaterTest.cpp
        )

add_library(wordDescriptionService ${SOURCES})
add_executable(wordDescriptionServiceUT ${SOURCES} ${UT_SOURCES})

target_compile_definitions(wordDescriptionServiceUT PUBLIC -DGTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(wordDescriptionService
        PUBLIC
        "include"
        PRIVATE
        "include/wordDescriptionService"
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(wordDescriptionServiceUT
        PRIVATE
        "include"
        "include/wordDescriptionService"
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )

target_link_libraries(wordDescriptionService PUBLIC
        utils
        wordDescriptionDownloader
        wordDescriptionRepository
        )
target_link_libraries(wordDescriptionServiceUT PRIVATE
        gmock_main
        gtest
        utils
        wordDescriptionDownloader
        wordDescriptionRepository
        )

target_compile_options(wordDescriptionService PUBLIC ${FLAGS})
target_compile_options(wordDescriptionServiceUT PUBLIC)

add_test(wordDescriptionServiceUT wordDescriptionServiceUT --gtest_color=yes)
