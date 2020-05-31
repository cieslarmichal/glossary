
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
add_executable(wordDescriptionServiceUT ${UT_SOURCES})

target_include_directories(wordDescriptionService
        PUBLIC "include"
        PRIVATE "include/wordDescriptionService"
        )
target_include_directories(wordDescriptionServiceUT PRIVATE
        "include"
        "include/wordDescriptionService"
        )

target_link_libraries(wordDescriptionService PUBLIC
        utils
        wordDescriptionDownloader
        wordDescriptionRepository
        )
target_link_libraries(wordDescriptionServiceUT PRIVATE
        gtest_main
        gmock
        utils
        wordDescriptionService
        wordDescriptionDownloader
        wordDescriptionRepository
        )

target_compile_options(wordDescriptionService PUBLIC ${FLAGS})
target_compile_options(wordDescriptionServiceUT PUBLIC -Wall -Wextra -Werror)

add_test(wordDescriptionServiceUT wordDescriptionServiceUT --gtest_color=yes)
