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
add_executable(wordDescriptionDownloaderUT ${SOURCES} ${UT_SOURCES})

target_compile_definitions(wordDescriptionDownloaderUT PUBLIC -DGTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(wordDescriptionDownloader
        PUBLIC
        "include"
        PRIVATE
        "include/wordDescriptionDownloader"
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}

        )
target_include_directories(wordDescriptionDownloaderUT PRIVATE
        "include"
        "include/wordDescriptionDownloader"
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        ${JSON_INCLUDE_DIR}
        )

target_link_libraries(wordDescriptionDownloader
        PUBLIC webConnection
        PRIVATE utils wordDescriptionRepository
        )
target_link_libraries(wordDescriptionDownloaderUT PRIVATE
        gmock_main
        gtest
        utils
        webConnection
        wordDescriptionRepository
        )

target_compile_options(wordDescriptionDownloader PUBLIC ${FLAGS})
target_compile_options(wordDescriptionDownloaderUT PUBLIC)

add_test(wordDescriptionDownloaderUT wordDescriptionDownloaderUT --gtest_color=yes)

