set(SOURCES
        src/clients/GoogleTranslateClientImpl.cpp
        src/repositories/DefaultTranslationRepository.cpp
        src/serializers/TranslationsJsonSerializer.cpp
        src/repositories/TranslationsMemoryStorage.cpp
        src/repositories/TranslationsPersistentStorage.cpp
        src/queries/GetSupportedLanguagesQueryImpl.cpp
        src/queries/GetTranslationQueryImpl.cpp
        src/factories/TranslationFactory.cpp
        src/factories/TranslationFactoryImpl.cpp
        )

set(UT_SOURCES
        src/clients/GoogleTranslateClientImplTest.cpp
        src/repositories/DefaultTranslationRepositoryTest.cpp
        src/serializers/TranslationsJsonSerializerTest.cpp
        src/repositories/TranslationsMemoryStorageTest.cpp
        src/repositories/TranslationsPersistentStorageTest.cpp
        src/queries/GetSupportedLanguagesQueryImplTest.cpp
        src/queries/GetTranslationQueryImplTest.cpp
        )

add_library(translation ${SOURCES})
add_executable(translationUT ${SOURCES} ${UT_SOURCES})

target_include_directories(translation
        PUBLIC
        "include"
        PRIVATE
        "include/translation"
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(translationUT PRIVATE
        "include/translation"
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
target_compile_options(translationUT PUBLIC ${FLAGS})

add_test(translationUT translationUT --gtest_color=yes)
