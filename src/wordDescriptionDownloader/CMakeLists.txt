set(SOURCES
        src/DefaultDescriptionParser.cpp
        src/HtmlDescriptionLinesSelector.cpp
        src/DefaultWordDescriptionDownloader.cpp
        src/WordDescriptionDownloaderFactory.cpp
        src/DefaultWordDescriptionDownloaderFactory.cpp
        )

set(UT_SOURCES
        src/DefaultDescriptionParserTest.cpp
        src/HtmlDescriptionLinesSelectorTest.cpp
        src/DefaultWordDescriptionDownloaderTest.cpp
        )

add_library(wordDescriptionDownloader ${SOURCES})
add_executable(wordDescriptionDownloaderUT ${UT_SOURCES})

target_include_directories(wordDescriptionDownloader
        PUBLIC "include"
        PRIVATE "include/wordDescriptionDownloader"
        )
target_include_directories(wordDescriptionDownloaderUT PRIVATE
        ${INTERNAL_LIBS_INCLUDE_PATH}
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

