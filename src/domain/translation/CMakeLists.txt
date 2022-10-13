set(SOURCES
        src/DefaultTranslationService.cpp
        src/GoogleTranslateApiJsonResponseDeserializer.cpp
        src/TranslatorFactory.cpp
        src/DefaultTranslationServiceFactory.cpp
        src/DefaultTranslationRepository.cpp
        src/TranslationsJsonSerializer.cpp
        src/TranslationsMemoryStorage.cpp
        src/TranslationsPersistentStorage.cpp
        src/TranslationRepositoryFactory.cpp
        src/DefaultTranslationRepositoryFactory.cpp
        )

set(UT_SOURCES
        src/DefaultTranslationServiceTest.cpp
        src/GoogleTranslateApiJsonResponseDeserializerTest.cpp
        src/DefaultTranslationRepositoryTest.cpp
        src/TranslationsJsonSerializerTest.cpp
        src/TranslationsMemoryStorageTest.cpp
        src/TranslationsPersistentStorageTest.cpp
        )

add_library(translation ${SOURCES})
add_executable(translationUT ${SOURCES} ${UT_SOURCES})

target_include_directories(translation
        PUBLIC "include"
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(translationUT PRIVATE
        "include"
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )

target_link_libraries(translation
        PUBLIC httpClient
        PRIVATE utils
        fmt::fmt
        )
target_link_libraries(translationUT PRIVATE
        gmock_main
        gtest
        utils
        httpClient
        fmt::fmt
        )

target_compile_options(translation PUBLIC ${FLAGS})

add_test(translationUT translationUT --gtest_color=yes)
