set(SOURCES
        src/TranslationServiceFactory.cpp
        src/DefaultTranslationServiceFactory.cpp
        src/DefaultTranslationRetrieverService.cpp
        src/SupportedLanguagesRetriever.cpp
        src/TranslateApiKeyFileReader.cpp
        src/ApiKeyFromFileContentRetriever.cpp
        src/DefaultTranslatorConnectionChecker.cpp
        )

set(UT_SOURCES
        src/DefaultTranslationRetrieverServiceTest.cpp
        src/SupportedLanguagesRetrieverTest.cpp
        src/TranslateApiKeyFileReaderTest.cpp
        src/ApiKeyFromFileContentRetrieverTest.cpp
        src/DefaultTranslatorConnectionCheckerTest.cpp
        )

add_library(translationService ${SOURCES})
add_executable(translationServiceUT ${UT_SOURCES})

target_include_directories(translationService PUBLIC "include" PRIVATE "include/translationService")
target_include_directories(translationServiceUT PRIVATE "include" "include/translationService")

target_link_libraries(translationService PRIVATE utils translationRepository translator)
target_link_libraries(translationServiceUT PRIVATE gtest_main gmock utils translationService translationRepository translator)

target_compile_options(translationService PUBLIC ${FLAGS})
target_compile_options(translationServiceUT PUBLIC -Wall -Wextra -Werror)

add_test(translationServiceUT translationServiceUT --gtest_color=yes)
