set(SOURCES
        src/services/DefaultTranslationService.cpp
        src/serializers/GoogleTranslateApiJsonResponseDeserializer.cpp
        src/repositories/DefaultTranslationRepository.cpp
        src/serializers/TranslationsJsonSerializer.cpp
        src/repositories/TranslationsMemoryStorage.cpp
        src/repositories/TranslationsPersistentStorage.cpp
        )

set(UT_SOURCES
        src/services/DefaultTranslationServiceTest.cpp
        src/serializers/GoogleTranslateApiJsonResponseDeserializerTest.cpp
        src/repositories/DefaultTranslationRepositoryTest.cpp
        src/serializers/TranslationsJsonSerializerTest.cpp
        src/repositories/TranslationsMemoryStorageTest.cpp
        src/repositories/TranslationsPersistentStorageTest.cpp
        )

add_library(translation ${SOURCES})
add_executable(translationUT ${SOURCES} ${UT_SOURCES})

target_include_directories(translation
        PUBLIC
        "include"
        PRIVATE
        "include/translation"
        "include/translation/queries"
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(translationUT PRIVATE
        "include/translation"
        "include/translation/queries"
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )

target_link_libraries(translation
        PUBLIC httpClient
        PRIVATE
        fileSystem
        collection
        fmt::fmt
        )
target_link_libraries(translationUT PRIVATE
        gmock_main
        gtest
        fileSystem
        collection
        httpClient
        fmt::fmt
        )

target_compile_options(translation PUBLIC ${FLAGS})

add_test(translationUT translationUT --gtest_color=yes)
