set(SOURCES
        src/DefaultWordDescriptionDownloader.cpp
        src/WordDescriptionDownloaderFactory.cpp
        src/DefaultWordDescriptionDownloaderFactory.cpp
        src/WordsApiJsonResponseDeserializer.cpp
        src/WordsApiResponseFetcher.cpp
        )

set(UT_SOURCES
        src/DefaultWordDescriptionDownloaderTest.cpp
        src/WordsApiJsonResponseDeserializerTest.cpp
        src/WordsApiResponseFetcherTest.cpp
        )

add_library(wordDescriptionDownloader ${SOURCES})
add_executable(wordDescriptionDownloaderUT ${UT_SOURCES})

target_include_directories(wordDescriptionDownloader
        PUBLIC "include"
        PRIVATE "include/wordDescriptionDownloader" ${JSON_INCLUDE_DIR}
        )
target_include_directories(wordDescriptionDownloaderUT PRIVATE
        ${INTERNAL_LIBS_INCLUDE_PATH}
        ${JSON_INCLUDE_DIR}
        "include"
        "include/wordDescriptionDownloader"
        )

target_link_libraries(wordDescriptionDownloader
        PUBLIC webConnection
        PRIVATE utils wordDescriptionRepository
        )
target_link_libraries(wordDescriptionDownloaderUT PRIVATE
        gtest_main
        gmock
        wordDescriptionDownloader
        wordDescriptionRepository
        utils
        webConnection
        )

target_compile_options(wordDescriptionDownloader PUBLIC ${FLAGS})
target_compile_options(wordDescriptionDownloaderUT PUBLIC -Wall -Wextra -Werror)

add_test(wordDescriptionDownloaderUT wordDescriptionDownloaderUT --gtest_color=yes)

