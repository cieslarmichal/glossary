set(SOURCES
        src/DefaultWordDescriptionRetrieverService.cpp
        src/WordDescriptionServiceFactory.cpp
        src/DefaultWordDescriptionServiceFactory.cpp
        )

set(UT_SOURCES
        src/DefaultWordDescriptionRetrieverServiceTest.cpp
        )

add_library(wordDescriptionService ${SOURCES})
add_executable(wordDescriptionServiceUT ${UT_SOURCES})

target_include_directories(wordDescriptionService PUBLIC "include" PRIVATE "include/wordDescriptionService")
target_include_directories(wordDescriptionServiceUT PRIVATE "include" "include/wordDescriptionService")

target_link_libraries(wordDescriptionService PRIVATE utils wordDescriptionDownloader wordDescriptionRepository)
target_link_libraries(wordDescriptionServiceUT PRIVATE gtest_main gmock utils wordDescriptionService wordDescriptionDownloader wordDescriptionRepository)

target_compile_options(wordDescriptionService PUBLIC ${FLAGS})
target_compile_options(wordDescriptionServiceUT PUBLIC -Wall -Wextra -Werror)

add_test(wordDescriptionServiceUT wordDescriptionServiceUT --gtest_color=yes)
