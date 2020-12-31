set(SOURCES
        src/TranslationServiceFactory.cpp
        src/DefaultTranslationServiceFactory.cpp
        src/DefaultTranslationService.cpp
        src/SupportedLanguagesRetriever.cpp
        src/TranslateApiKeyFileReader.cpp
        src/ApiKeyFromFileContentRetriever.cpp
        src/DefaultTranslatorConnectionChecker.cpp
        src/DefaultApiKeyLocationUpdater.cpp
        )

set(UT_SOURCES
        src/DefaultTranslationServiceTest.cpp
        src/SupportedLanguagesRetrieverTest.cpp
        src/TranslateApiKeyFileReaderTest.cpp
        src/ApiKeyFromFileContentRetrieverTest.cpp
        src/DefaultTranslatorConnectionCheckerTest.cpp
        src/DefaultApiKeyLocationUpdaterTest.cpp
        )

add_library(translationService ${SOURCES})
add_executable(translationServiceUT ${SOURCES} ${UT_SOURCES})

target_compile_definitions(translationServiceUT PUBLIC -DGTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(translationService
        PUBLIC
        "include"
        ${Boost_INCLUDE_DIR}
        PRIVATE
        "include/translationService"
        )
target_include_directories(translationServiceUT PRIVATE
        "include"
        "include/translationService"
        ${Boost_INCLUDE_DIR}
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        )

target_link_libraries(translationService PRIVATE
        utils
        translationRepository
        translator
        )
target_link_libraries(translationServiceUT PRIVATE
        gmock_main
        gtest
        utils
        translationRepository
        translator
        )

target_compile_options(translationService PUBLIC ${FLAGS})
target_compile_options(translationServiceUT PUBLIC)

add_test(translationServiceUT translationServiceUT --gtest_color=yes)
